#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

#define HISTORY_SIZE 10

int main()
{
    char command[1024];
    char current_dir[1024];
    char *history[HISTORY_SIZE] = {NULL};
    int history_index = 0;

    while(1)
    {
        while(waitpid(-1,NULL,WNOHANG) > 0);

        getcwd(current_dir, sizeof(current_dir));

        int has_pipe = 0;
        int pipe_fds[2];
        char *cmd1 = NULL;
        char *cmd2 = NULL;

        int background = 0;
        printf("mini-shell> ");
        fflush(stdout);
        if(fgets(command, sizeof(command), stdin) == NULL)
        {
            break; // Exit on EOF
        }

        if(history[history_index] != NULL)
            free(history[history_index]);

        command[strcspn(command, "\n")] = 0;

        char *pipe_pos = strchr(command, '|');
        if(pipe_pos != NULL)
        {
            has_pipe = 1;
            *pipe_pos = '\0';
            cmd1 = command;
            cmd2 = pipe_pos + 1;
        }

        history[history_index] = strdup(command);
        history_index = (history_index + 1) % HISTORY_SIZE;

        if(!has_pipe)
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
                    printf("PID: %d\n", pid);
                    continue;
                }

                wait(NULL); // Wait for child process to finish            
            }
        }
        else
        {
            char *args1[10], *args2[10];
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
    }

    for(int i = 0; i < HISTORY_SIZE; i++)
    {
    if(history[i] != NULL)
            free(history[i]);
    }

    return 0;
}