#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>


pthread_t Philosophers[50];
pthread_mutex_t chopsticks[50];
struct timeval current_time,start;

void *func(void *val)
{
    int i = (long)val;
    printf("Philosopher %d is thinking\n", i);
    pthread_mutex_lock(&chopsticks[i]);
    gettimeofday(&current_time, NULL);
    printf("%ld ms Philosopher %d has taking a fork\n",-1 * ((start.tv_sec-current_time.tv_sec)*1000000 + start.tv_usec - current_time.tv_usec),i);
    pthread_mutex_lock(&chopsticks[(i + 1) % 50]);
    gettimeofday(&current_time, NULL);
    printf("%ld ms Philosopher %d has taking a fork\n",-1 *((start.tv_sec-current_time.tv_sec)*1000000 + start.tv_usec - current_time.tv_usec),i);
    printf("Philosopher %d is eating\n",i);
    sleep(3);
     gettimeofday(&current_time, NULL);
    pthread_mutex_unlock(&chopsticks[i]);
    pthread_mutex_unlock(&chopsticks[(i + 1) % 50]);
    printf("Philosopher %d finished eating in %ld ms\n",i,-1 * ((start.tv_sec-current_time.tv_sec)*1000000 + start.tv_usec - current_time.tv_usec));
    return (NULL);
}

int check_args(char **ag)
{
    int i = 0;
    while (ag[i])
    {
        /* code */
    }
    
}

int main(int ac,char **ag)
{
    int i;

    if(ac < 5 || ac > 6)
    {
        printf("ARGS : [ NUMBER_OF_PHIL | TIME_TO_DIE | TIME_TO_EAT | TIME_TO_SLEEP | NUMBER_OF_PHILOSOPHER_MUST_EAT ]");
        exit(0);
    }
    i = 0;
    gettimeofday(&start, NULL);
    while (i < 50)
    {
        pthread_mutex_init(&chopsticks[i], NULL);
        i++;
    }

    i = 0;
    while (i < 50)
    {
        pthread_create(&Philosophers[i], NULL, (void *)func, (void *)(long)i);
        i++;
    }

    i = 0;
    while (i < 50)
    {
        pthread_join(Philosophers[i], NULL);
        i++;
    }
}