#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void handle_sigint(int sig)
{
    if(sig == SIGINT)
    {
        printf("\nReceived SIGINT (Ctrl+C). Exiting gracefully...\n");
    }
    else if(sig == SIGTERM)
    {
        printf("\nReceived SIGTERM. Exiting gracefully...\n");
    }
    printf("Exiting gracefully...\n");
    exit(0);
}

int main()
{
    if(signal(SIGINT, handle_sigint) == SIG_ERR)
    {
        perror("Error setting up SIGINT handler");
        exit(EXIT_FAILURE);
    }

    if(signal(SIGTERM, handle_sigint) == SIG_ERR)
    {
        perror("Error setting up SIGTERM handler");
        exit(EXIT_FAILURE);
    }

    printf("Press Ctrl+C to exit the program\n");
    while(1)
    {
        sleep(1);
    }
    return 0;
}