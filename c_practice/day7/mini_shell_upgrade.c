#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

int main()
{
    char command[1024];

    while(1)
    {
        while(waitpid(-1,NULL,WNOHANG) > 0);

        int background = 0;
        printf("mini-shell> ");
        fflush(stdout);
        if(fgets(command, sizeof(command), stdin) == NULL)
        {
            break; // Exit on EOF
        }

        command[strcspn(command, "\n")] = 0;

        if(strcmp(command, "exit") == 0)
        {
            break; // Exit on "exit" command
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
            
            if(background == 1)
            {
                printf("PID: %d\n", pid);
                continue;
            }

            wait(NULL); // Wait for child process to finish

            if(file_redirect == 1)
                close(redirect_fd);

            
        }
    }

    return 0;
}