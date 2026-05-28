#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    char command[1024];

    while(1)
    {
        printf("mini-shell> ");
        if(fgets(command, sizeof(command), stdin) == NULL)
        {
            break; // Exit on EOF
        }

        command[strcspn(command, "\n")] = 0;

        char *commands_with_flags[100];
        char *token = strtok(command, " ");
        int i = 0;
        while(token != NULL)
        {         
            commands_with_flags[i++] = token;
            token = strtok(NULL, " ");
        }
        commands_with_flags[i] = NULL; // Null-terminate the array        

        if(strcmp(command, "exit") == 0)
        {
            break; // Exit on "exit" command
        }

        pid_t pid = fork();
        if(pid < 0)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        else if(pid == 0)
        {
            //Child process
            execvp(commands_with_flags[0], commands_with_flags);
            perror("execvp");
            exit(EXIT_FAILURE);
        }
        else
        {
            // Parent process
            wait(NULL); // Wait for child process to finish
        }
    }

    return 0;
}