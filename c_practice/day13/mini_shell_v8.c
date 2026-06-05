#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/types.h>
#include <time.h>

#define HISTORY_SIZE 10
#define JOB_SIZE 10

int main()
{
    char command[1024];
    char current_dir[1024];
    char *history[HISTORY_SIZE] = {NULL};
    int history_index = 0;
    int job_index = 0;
    int jobs_list[10] = {0};

    struct timespec start, end;

    while(1)
    {
        while(waitpid(-1,NULL,WNOHANG) > 0);

        getcwd(current_dir, sizeof(current_dir));

        int has_pipe = 0;
        int pipe_fds[2];
        char *cmd1 = NULL;
        char *cmd2 = NULL;

        int background = 0;

        int has_and = 0;
        char *and_cmd1 = NULL;
        char *and_cmd2 = NULL;
        
        printf("mini-shell> ");
        fflush(stdout);
        if(fgets(command, sizeof(command), stdin) == NULL)
        {
            break; // Exit on EOF
        }

        if(history[history_index] != NULL)
            free(history[history_index]);

        if(clock_gettime(CLOCK_MONOTONIC, &start) == -1)
        {
            perror("clock_gettime start failed");
            return 1;
        }
        int exec_time_print = 0;

        command[strcspn(command, "\n")] = 0;

        history[history_index] = strdup(command);
        history_index = (history_index + 1) % HISTORY_SIZE;

        char *pipe_pos = strchr(command, '|');
        if(pipe_pos != NULL)
        {
            has_pipe = 1;
            *pipe_pos = '\0';
            cmd1 = command;
            cmd2 = pipe_pos + 1;
        }

        char *and_pos = strstr(command, "&&");
        if(and_pos != NULL)
        {
            has_and = 1;
            *and_pos = '\0';
            cmd1 = command;
            cmd2 = and_pos+2;
        }

        
        if(has_pipe || has_and)
        {
            char *args1[100], *args2[100];
            int i = 0;
            char *token = strtok(cmd1, " ");
            while(token != NULL)
            {
                args1[i++] = token;
                token = strtok(NULL, " ");
            }
            args1[i] = NULL;

            i = 0;
            token = strtok(cmd2, " ");
            while(token != NULL)
            {
                args2[i++] = token;
                token = strtok(NULL, " ");
            }
            args2[i] = NULL;

            if(has_pipe)
            {

                if(pipe(pipe_fds) == -1)
                {
                    perror("Pipe Failed");
                    return 1;
                }

                pid_t pid1 = fork();
                if(pid1 < 0)
                {
                    perror("Fork failed");
                    return 1;
                }
                else if(pid1 == 0)
                {
                    close(pipe_fds[0]);
                    dup2(pipe_fds[1], STDOUT_FILENO);
                    close(pipe_fds[1]);

                    execvp(args1[0], args1);
                    perror("execvp");
                    exit(EXIT_FAILURE);
                }
                
                pid_t pid2 = fork();
                if(pid2 < 0)
                {
                    perror("Fork failed");
                    return 1;
                }
                else if(pid2 == 0)
                {
                    close(pipe_fds[1]);
                    dup2(pipe_fds[0], STDIN_FILENO);
                    close(pipe_fds[0]);

                    execvp(args2[0], args2);
                    perror("execvp");
                    exit(EXIT_FAILURE);
                }

                close(pipe_fds[0]);
                close(pipe_fds[1]);

                waitpid(pid1, NULL, 0);
                waitpid(pid2, NULL, 0);
            }
            else if(has_and)
            {
                pid_t pid1 = fork();
                int cmd_fail = 0;
                if(pid1 < 0)
                {
                    perror("Fork failed");
                    return 1;
                }
                else if(pid1 == 0)
                {
                    execvp(args1[0], args1);
                    perror("execvp");
                    exit(EXIT_FAILURE);
                }
                else
                {
                    int status;
                    waitpid(pid1, &status, 0);

                    if(WIFEXITED(status) && WEXITSTATUS(status) != 0)
                    {
                        cmd_fail = 1;
                    }

                }

                if(!cmd_fail)
                {
                    pid_t pid2 = fork();
                    if(pid2 < 0)
                    {
                        perror("Fork failed");
                        return 1;
                    }
                    else if(pid2 == 0)
                    {
                        execvp(args2[0], args2);
                        perror("execvp");
                        exit(EXIT_FAILURE);
                    }
                    else
                        waitpid(pid2, NULL, 0);
                }
            }

        }
        else
        {
            if(strcmp(command, "exit") == 0)
            {
                break; // Exit on "exit" command
            }
            if(strcmp(command, "history") == 0)
            {
                int command_count = 0;
                for(int i = 0; i < HISTORY_SIZE; i++)
                {
                    if(history[(history_index + i) % HISTORY_SIZE] == NULL)
                        continue;
                    else
                    {
                        printf("%d %s\n", (++command_count), history[(history_index + i) % HISTORY_SIZE]);
                    }
                }
                continue;
            }
            if(strcmp(command, "pwd") == 0)
            {
                printf("%s\n", current_dir);
                continue;
            }
            if(strcmp(command, "jobs") == 0)
            {
                int counter = 0;
                for(int i = 0; i < JOB_SIZE; i++)
                {
                    if((jobs_list[(job_index + i) % JOB_SIZE] != 0) && (waitpid(jobs_list[(job_index + i) % JOB_SIZE], NULL, WNOHANG) == 0))
                    {
                        printf("[%d] %d Running\n", (++counter), jobs_list[(job_index + i) % JOB_SIZE]);
                    }                    
                }
                continue;
            }

            size_t len = strlen(command);
            if(len > 0 && command[len - 1] == '&')
            {
                background = 1;
                command[len - 1] = '\0'; // Remove '&' from command
            }

            char *commands_with_flags[100];
            // memset(commands_with_flags, 0, sizeof(commands_with_flags));
            char *token = strtok(command, " ");
            int i = 0;
            int file_redirect = 0;
            int redirect_fd;
            while(token != NULL)
            {
                if(*token == '>')
                {
                    file_redirect = 1;
                    char *file_name = token = strtok(NULL, " ");
                    redirect_fd = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
                    if(redirect_fd < 0)
                    {
                        perror("open");
                        exit(EXIT_FAILURE);
                    }
                }
                else        
                    commands_with_flags[i++] = token;
                token = strtok(NULL, " ");
            }
            commands_with_flags[i] = NULL; // Null-terminate the array    
            
            if(commands_with_flags[0] == NULL)
            {
                continue; // No command entered
            }
            else if(strcmp(commands_with_flags[0], "cd") == 0)
            {
                if(commands_with_flags[1] && (strcmp(commands_with_flags[1], "..") == 0))
                    if(chdir("..") < 0)
                    {
                        perror("Failed to change directory");
                        exit(EXIT_FAILURE);
                    }

                continue;
            }
            else if(strcmp(commands_with_flags[0], "time") == 0)
                exec_time_print = 1;


            pid_t pid = fork();
            if(pid < 0)
            {
                perror("fork");
                exit(EXIT_FAILURE);
            }
            else if(pid == 0)
            {
                if(file_redirect == 1)
                    dup2(redirect_fd, STDOUT_FILENO);
                
                execvp(commands_with_flags[0], commands_with_flags);
                perror("execvp");
                exit(EXIT_FAILURE);
            }
            else
            {

                if(file_redirect == 1)
                {
                    close(redirect_fd);
                }
                
                if(background == 1)
                {
                    jobs_list[job_index] = pid;
                    job_index = (job_index + 1) % JOB_SIZE;
                    printf("PID: %d\n", pid);
                    continue;
                }

                wait(NULL); // Wait for child process to finish     
                
                if(exec_time_print == 1)
                {
                    if(clock_gettime(CLOCK_MONOTONIC, &end) == -1)
                    {
                        perror("Failed to get clock end time");
                        return 1;
                    }
                    double total_exec_time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec)/1000000000;
                    printf("Total execution time: %.2f seconds\n", total_exec_time);
                }
            }
        }
    }

    for(int i = 0; i < HISTORY_SIZE; i++)
    {
    if(history[i] != NULL)
            free(history[i]);
    }

    return 0;
}