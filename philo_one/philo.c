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
//        printf("----------------------------------------------------\n");
    if(philo->state[i] != EAT)
    {
        printf("%d ms Philosopher %d is thinking\n",get_current() - philo->current_time, i);
    }
    if(!pthread_mutex_lock(&philo->forks[i]))
    {
        gettimeofday(&current_time,NULL);
        printf("%d ms Philosopher %d has taking a fork\n",get_current() - philo->current_time,i);
        j++;
    }
    if(!pthread_mutex_lock(&philo->forks[(i + 1) % philo->number_phil]))
    {
        gettimeofday(&current_time, NULL);
        printf("%ld ms Philosopher %d has taking a fork left\n",get_current() - philo->current_time,i);
        printf("%ld ms Philosopher %d is eating\n",get_current() - philo->current_time,i);
        j++;
    }
    if(j == 2)
    {
        philo->state[i] = EAT;
        gettimeofday(&current_time, NULL);
        usleep(philo->time_to_eat * 1000);
        philo->state[i] = NOT_EAT;
        pthread_mutex_unlock(&philo->forks[i]);
        pthread_mutex_unlock(&philo->forks[(i + 1) % philo->number_phil]);
        philo->last_time_eat[i] = ft_itoa(get_current());
        printf("%ld ms Philosopher %d is sleeping\n",get_current() - philo->current_time, i);
        usleep(philo->time_to_sleep*1000);
        j = 0;
    }
    else if(philo->last_time_eat[i])
    {

    }
    func(philo);
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
    printf("----TIME---------PHILOSOPHER---------OPERATION------\n");
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
        printf("----------------------------------------------------\n");
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