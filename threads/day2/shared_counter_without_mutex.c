#include <stdio.h>
#include <pthread.h>
#include <stdint.h>

int counter = 0;

void *inc_counter(void *arg)
{
    uint8_t num = (uint8_t)arg;
    for(int i = 0; i<100000; i++)
    {
        counter++;
    }
    return NULL;
}

int main()
{
    pthread_t thread1, thread2, thread3, thread4;
    
    pthread_create(&thread1, NULL, inc_counter, (void *)0);
    pthread_create(&thread2, NULL, inc_counter, (void *)1);
    pthread_create(&thread3, NULL, inc_counter, (void *)2);
    pthread_create(&thread4, NULL, inc_counter, (void *)3);


    printf("Inside Main:\n");

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);
    pthread_join(thread4, NULL);

    printf("Final counter value: %d\n", counter);

    printf("Finish execution\n");

    return 0;
}