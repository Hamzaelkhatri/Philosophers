#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>


pthread_t Philosophers[5];
pthread_mutex_t chopsticks[5];
struct timeval current_time,start;

void *func(void *val)
{
    int i = (long)val;
    printf("Philosopher %d is thinking\n", i);
    pthread_mutex_lock(&chopsticks[i]);
    gettimeofday(&current_time, NULL);
    printf("%ld ms Philosopher %d has taking a fork\n",(current_time.tv_sec * 1000000 + current_time.tv_usec) - (start.tv_sec + start.tv_usec),i);
    pthread_mutex_lock(&chopsticks[(i + 1) % 5]);
    gettimeofday(&current_time, NULL);
    printf("%ld ms Philosopher %d has taking a fork\n",(current_time.tv_sec * 1000000 + current_time.tv_usec) - (start.tv_sec + start.tv_usec),i);
    printf("Philosopher %d is eating\n",i);
    sleep(3);
     gettimeofday(&current_time, NULL);
    int sleeptime = (current_time.tv_sec * 1000000 + current_time.tv_usec) - (start.tv_sec + start.tv_usec);
    pthread_mutex_unlock(&chopsticks[i]);
    pthread_mutex_unlock(&chopsticks[(i + 1) % 5]);
    printf("Philosopher %d finished eating in %d ms\n",i,sleeptime);
    return (NULL);
}

int main()
{
    int i;

    i = 0;
    gettimeofday(&start, NULL);
    while (i < 5)
    {
        pthread_mutex_init(&chopsticks[i], NULL);
        i++;
    }

    i = 0;
    while (i < 5)
    {
        pthread_create(&Philosophers[i], NULL, (void *)func, (void *)(long)i);
        i++;
    }

    i = 0;
    while (i < 5)
    {
        pthread_join(Philosophers[i], NULL);
        i++;
    }
}