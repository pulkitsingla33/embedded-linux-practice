#include <stdio.h>
#include <pthread.h>
#include <stdint.h>

int counter = 0;
pthread_mutex_t lock;

void *inc_counter(void *arg)
{
    uint8_t num = (uint8_t)arg;
    for(int i = 0; i<100000; i++)
    {
        pthread_mutex_lock(&lock);
        counter++;
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

int main()
{
    pthread_t thread1, thread2;
    pthread_mutex_init(&lock, NULL);
    
    pthread_create(&thread1, NULL, inc_counter, (void *)0);
    pthread_create(&thread2, NULL, inc_counter, (void *)1);

    printf("Inside Main:\n");

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    pthread_mutex_destroy(&lock);

    printf("Final counter value: %d\n", counter);

    printf("Finish execution\n");

    return 0;
}