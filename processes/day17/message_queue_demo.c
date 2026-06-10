#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <mqueue.h>

#define QUEUE_NAME "/my_test_queue"
#define MAX_SIZE 1024
#define MSG_STOP "exit"

int main()
{
    mqd_t mq;
    struct mq_attr attr;
    pid_t pid;
    char buffer[MAX_SIZE];

    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = MAX_SIZE;
    attr.mq_curmsgs = 0;

    mq = mq_open(QUEUE_NAME, O_CREAT | O_RDWR, 0644, &attr);
    if(mq == (mqd_t)-1)
    {
        perror("Parent: mq_open failed");
        exit(1);
    }

    pid = fork();
    if(pid < 0)
    {
        perror("Fork failed");
        mq_close(mq);
        mq_unlink(QUEUE_NAME);
        exit(1);
    }
    if(pid > 0)
    {
        const char *msg = "Hello from Parent!";
        printf("Sending message from parent\n");

        if(mq_send(mq, msg, strlen(msg) + 1, 0) == -1)
        {
            perror("Parent: mq_send failed");
        }

        wait(NULL);

        mq_close(mq);
        mq_unlink(QUEUE_NAME);
        printf("Parent: Queue closed\n");
    }
    else
    {
        unsigned int prio;
        printf("Child waiting to receive message\n");

        ssize_t bytes_read = mq_receive(mq, buffer, MAX_SIZE, &prio);
        if(bytes_read >= 0)
        {
            printf("Child: Received message: %s\n", buffer);
        }
        else
        {
            perror("Child mq_receive failed");
        }

        mq_close(mq);
        printf("Child connection closed\n");
        exit(0);
    }

    return 0;
}