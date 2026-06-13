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
#define SEQUENTIAL_COMMANDS_MAX 5

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

        char *or_pos = strstr(command, "||");
        int has_or = 0;
        if(or_pos != NULL)
        {
            has_or = 1;
            *or_pos = '\0';
            cmd1 = command;
            cmd2 = or_pos+2;
        }
        
        char *pipe_pos = strchr(command, '|');
        if((pipe_pos != NULL) && (or_pos == NULL))
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

        char *seq = strchr(command, ';');
        int has_seq = 0;
        if(seq != NULL)
            has_seq = 1;
        
        if(has_pipe || has_and || has_or)
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
            else if(has_or)
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

                if(cmd_fail)
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
        else if(has_seq)
        {
            char *seq_pos = strtok(command, ";");
            char *seq_commands[SEQUENTIAL_COMMANDS_MAX];
            int seq_counter = 0;
            while(seq_pos != NULL)
            {                
                seq_commands[seq_counter++] = seq_pos;
                seq_pos = strtok(NULL, ";");
                if(seq_counter == (SEQUENTIAL_COMMANDS_MAX - 1))
                {
                    printf("Can take only 4 sequential commands\n");
                    break;
                }
            }
            seq_commands[seq_counter] = NULL;  

            seq_counter = 0;
            while(seq_commands[seq_counter] != NULL)
            {
                char *args[100];
                char *seq_command_args = strtok(seq_commands[seq_counter], " ");
                int i = 0;
                while(seq_command_args != NULL)
                {
                    args[i++] = seq_command_args;
                    seq_command_args = strtok(NULL, " ");
                }
                args[i] = NULL;

                pid_t pid_val = fork();
                if(pid_val < 0)
                {
                    perror("Fork failed");
                    exit(EXIT_FAILURE);
                }
                else if(pid_val == 0)
                {
                    execvp(args[0], args);
                    perror("execvp failed");
                    exit(EXIT_FAILURE);
                }
                else
                {
                    seq_counter++;
                    waitpid(pid_val, NULL, 0);
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

            int in_quotes = 0, write_idx = 0;
            for(int read_idx = 0; command[read_idx] != '\0'; read_idx++)
            {
                if(command[read_idx] == '"')
                {
                    in_quotes = !in_quotes;
                    continue;
                }

                if(in_quotes && command[read_idx] == ' ')
                {
                    command[write_idx++] = '\x01';
                }
                else
                {
                    command[write_idx++] = command[read_idx];
                }
            }
            command[write_idx] ='\0';

            int output_redirect = 0, append_redirect = 0, err_redirect = 0;
            int out_redirect_fd = -1, append_redirect_fd = -1, err_redirect_fd = -1;
            char *redirect_new = strchr(command, '>');
            char *redirect_append = strstr(command, ">>");
            char *redirect_err = strstr(command, "2>");
            while((redirect_new != NULL) && ((*(redirect_new + 1) == '>') || (*(redirect_new - 1) == '2')))
            {
                if(*(redirect_new + 1) == '>')
                {
                    redirect_new += 2;
                }
                else if(*(redirect_new - 1) == '2')
                {
                    redirect_new += 1;
                }
            }
            if((redirect_new != NULL) || (redirect_append != NULL) || (redirect_err != NULL))
            {
                char *out_filename, *append_filename, *err_filename;
                if(redirect_append != NULL)
                {
                    append_redirect = 1;
                    *redirect_append = '\0';
                    append_filename = redirect_append + 2;
                    while(*append_filename == ' ')
                        append_filename++;
                    // redirect_fd = open(file_name, O_CREAT | O_WRONLY | O_APPEND, 0644);
                }
                if(redirect_err != NULL)
                {
                    *redirect_err = '\0';
                    err_redirect = 1;
                    err_filename = redirect_err + 2;
                    while(*err_filename == ' ')
                        err_filename++;
                    // redirect_fd = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
                }
                if(redirect_new != NULL)
                {
                    output_redirect = 1;
                    *redirect_new = '\0';
                    out_filename = redirect_new + 1;
                    while(*out_filename == ' ')
                        out_filename++;
                    // redirect_fd = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
                }
                
                if(append_redirect)
                {
                    append_redirect_fd = open(append_filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
                    if(append_redirect_fd < 0)
                    {
                        perror("open");
                        exit(EXIT_FAILURE);
                    }
                }
                if(err_redirect)
                {
                    err_redirect_fd = open(err_filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
                    if(err_redirect_fd < 0)
                    {
                        perror("open");
                        close(append_redirect_fd);
                        exit(EXIT_FAILURE);
                    }
                }
                if(output_redirect)
                {
                    out_redirect_fd = open(out_filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
                    if(out_redirect_fd < 0)
                    {
                        perror("open");
                        close(append_redirect_fd);
                        close(err_redirect_fd);
                        exit(EXIT_FAILURE);
                    }
                }
                
            }

            int input_redirect = 0;
            int input_redirect_fd;
            char *redirect_input = strchr(command, '<');
            if(redirect_input != NULL)
            {
                input_redirect = 1;
                *redirect_input = '\0';
                char *input_file_name = redirect_input + 1;
                while(*input_file_name == ' ')
                    input_file_name++;

                input_redirect_fd = open(input_file_name, O_RDONLY);
                if(input_file_name < 0)
                {
                    perror("Cannot open file");
                    exit(EXIT_FAILURE);
                }

            }

            char *commands_with_flags[100];
            // memset(commands_with_flags, 0, sizeof(commands_with_flags));
            char *token = strtok(command, " ");
            int i = 0;
            
            while(token != NULL)
            {    
                commands_with_flags[i++] = token;
                token = strtok(NULL, " ");
            }
            commands_with_flags[i] = NULL; // Null-terminate the array    

            for(int j = 0; commands_with_flags[j] != NULL; j++)
            {
                for(int k = 0; commands_with_flags[j][k]!='\0'; k++)
                {
                    if(commands_with_flags[j][k] == '\x01')
                        commands_with_flags[j][k] = ' ';
                }
            }
            
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
                if(err_redirect == 1)
                {
                    dup2(err_redirect_fd, STDERR_FILENO);
                }

                if(append_redirect == 1)
                {
                    dup2(append_redirect_fd, STDOUT_FILENO);
                }
                else if(output_redirect == 1)
                {
                    dup2(out_redirect_fd, STDOUT_FILENO);
                }

                if(input_redirect == 1)
                {
                    dup2(input_redirect_fd, STDIN_FILENO);
                }
                
                if(exec_time_print == 1)
                {
                    execvp(commands_with_flags[1], &commands_with_flags[1]);
                }
                else
                    execvp(commands_with_flags[0], commands_with_flags);
                perror("execvp");
                exit(EXIT_FAILURE);
            }
            else
            {

                if(append_redirect == 1)
                {
                    close(append_redirect_fd);
                }
                if(err_redirect == 1)
                {
                    close(err_redirect_fd);
                }
                if(output_redirect == 1)
                {
                    close(out_redirect_fd);
                }
                if(input_redirect == 1)
                {
                    close(input_redirect_fd);
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