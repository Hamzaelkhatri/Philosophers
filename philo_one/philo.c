#include "philosophers.h"

struct timeval current_time,start;

void *func(void *val)
{
    t_philo *philo;
    int i;

    philo =(t_philo *)val;
    i = philo->index_of_phil;
    philo->index_of_phil++;
    printf("Philosopher %d is thinking\n", philo->index_of_phil);
    pthread_mutex_lock(&philo->forks[i]);
    gettimeofday(&current_time,NULL);
    printf("%ld ms Philosopher %d has taking a fork\n",-1 * ((start.tv_sec-current_time.tv_sec)*1000000 + start.tv_usec - current_time.tv_usec),i);
    pthread_mutex_lock(&philo->forks[(i + 1) % philo->number_phil]);
    gettimeofday(&current_time, NULL);
    printf("%ld ms Philosopher %d has taking a fork\n",-1 *((start.tv_sec-current_time.tv_sec)*1000000 + start.tv_usec - current_time.tv_usec),i);
    printf("Philosopher %d is eating\n",i);
    // sleep(1);
    usleep(philo->time_to_eat*1000);
    gettimeofday(&current_time, NULL);
    pthread_mutex_unlock(&philo->forks[i]);
    pthread_mutex_unlock(&philo->forks[(i + 1) % philo->number_phil]);
    printf("Philosopher %d finished eating in %ld ms\n",i,-1 * ((start.tv_sec-current_time.tv_sec)*1000000 + start.tv_usec - current_time.tv_usec));
    val = (void *)philo;
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

void init_mutex(t_philo *philo)
{
    int i;

    i = 0;
    while(i < philo->number_phil)
    {
         pthread_mutex_init(&philo->forks[i], NULL);
         i++;
    }
}

void do_stuff(t_philo *philo)
{
    int i;

    i = 0;
    while (i < philo->number_phil)
    {
        // philo->index_of_phil = i;
        pthread_create(&philo->Philosophers[i], NULL, (void *)func, (void *)philo);
        // printf("[%i]",i);
        i++;
    }

}

void waiting_threads(t_philo *philo)
{
    int i;

    i = 0;
    while (i < philo->number_phil)
    {
        pthread_join(philo->Philosophers[i], NULL);
        i++;
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

    t_philo *philosopher;
    philosopher = NULL;
    philosopher =init(ag);
    init_mutex(philosopher);
    gettimeofday(&start, NULL);
    do_stuff(philosopher);
    waiting_threads(philosopher);
    // i = 0;
    // while (i < 50)
    // {
    //     pthread_mutex_init(&chopsticks[i], NULL);
    //     i++;
    // }

    // i = 0;
    // while (i < 50)
    // {
    //     pthread_create(&Philosophers[i], NULL, (void *)func, (void *)(long)i);
    //     i++;
    // }

    // i = 0;
}