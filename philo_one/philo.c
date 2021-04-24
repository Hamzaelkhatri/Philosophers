#include "philosophers.h"

struct timeval current_time,start;

void *func(void *val)
{
    t_philo *philo;
    int i;
    int j;

    philo =(t_philo *)val;
    j =0;
    i = philo->index_of_phil;
    if(i < philo->number_phil)
        philo->index_of_phil++;
    else 
    {
        philo->index_of_phil = 0;
        i = 0;
    }

    if(philo->state[i] != EAT)
        printf("Philosopher %d is thinking\n", i);
    if(!pthread_mutex_lock(&philo->forks[i]))
    {
        gettimeofday(&current_time,NULL);
        printf("%ld ms Philosopher %d has taking a fork 1\n",-1 *((start.tv_usec-current_time.tv_usec)/10000 + start.tv_usec - current_time.tv_usec),i);
        j++;
    }
    if(!pthread_mutex_lock(&philo->forks[(i + 1) % philo->number_phil]))
    {
        gettimeofday(&current_time, NULL);
        printf("%ld ms Philosopher %d has taking a fork 2\n",-1 *((start.tv_usec-current_time.tv_usec)/10000 + start.tv_usec - current_time.tv_usec),i);
        printf("Philosopher %d is eating\n",i);
        j++;
    }
    if(j == 2)
        philo->state[i] = EAT;
    usleep(philo->time_to_eat*1000);
    gettimeofday(&current_time, NULL);
    pthread_mutex_unlock(&philo->forks[i]);
    pthread_mutex_unlock(&philo->forks[(i + 1) % philo->number_phil]);
    if(j == 2)
    {
        printf("Philosopher %d finished eating in %ld ms\n",i,-1 *((start.tv_usec-current_time.tv_usec)/10000 + start.tv_usec - current_time.tv_usec));
        printf("Philosopher %d is sleeping\n", i);
        philo->state[i] = NOT_EAT;
        usleep(philo->time_to_sleep*1000);
    }
    func(philo);
    val = (void *)philo;
    return (val);
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
        pthread_create(&philo->Philosophers[i], NULL, (void *)func, (void *)philo);
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

void destroy_mutex(t_philo *philo)
{
    int i;

    i = 0;
    while (i < philo->number_phil)
    {
        pthread_mutex_destroy(&philo->forks[i]);
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
    destroy_mutex(philosopher);
}