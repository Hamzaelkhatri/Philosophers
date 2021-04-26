#include "philosophers.h"

void *func(void *val)
{
    t_philo *philo;
    struct timeval current_time;
    int i;
    int j;

    philo = (t_philo *)val;
    j = 0;
    i = philo->index_of_phil;
    if (i < philo->number_phil)
        philo->index_of_phil++;
    else
    {
        philo->index_of_phil = 0;
        i = 0;
        while (i < philo->number_phil)
        {
            philo->state[i] = NAN;
            i++;
        }

        i = 0;
    }
    if (philo->state[i] == NAN || philo->state[i] == THINKING || philo->state[i] == SLEEPING)
    {
        printf("\e[0;31m %d ms Philosopher %d is thinking\n", get_current() - philo->current_time, i);
        philo->state[i] = THINKING;
    }
    if (philo->state[i] == THINKING && !pthread_mutex_lock(&philo->forks[i])) // && philo->state[i] != EAT
    {
        printf("\e[0;32m %d ms Philosopher %d has taking a fork 1\n", get_current() - philo->current_time, i);
        j++;
    }
    if (philo->state[i] == THINKING && !pthread_mutex_lock(&philo->forks[(i + 1) % philo->number_phil])) // && philo->state[i] != EAT
    {
        printf("\e[0;32m %ld ms Philosopher %d has taking a fork 2\n", get_current() - philo->current_time, i);
        j++;
    }
    if (j == 2)
    {
        printf("\e[1;34m %ld ms Philosopher %d is eating\n", get_current() - philo->current_time, i);
        philo->state[i] = EAT;
        usleep(philo->time_to_eat * 1000);
        pthread_mutex_unlock(&philo->forks[i]);
        pthread_mutex_unlock(&philo->forks[(i + 1) % philo->number_phil]);
        printf("\e[0;35m %ld ms Philosopher %d is sleeping\n", get_current() - philo->current_time, i);
        philo->state[i] = SLEEPING;
        usleep(philo->time_to_sleep * 1000);
        philo->state[i] = NAN;
        j = 0;
    }
    else
    {
        philo->state[i] = THINKING;
    }
    usleep(20);
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
    while (i < philo->number_phil)
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

int main(int ac, char **ag)
{
    int i;

    if (ac < 5 || ac > 6)
    {
        printf("ARGS : [ NUMBER_OF_PHIL | TIME_TO_DIE | TIME_TO_EAT | TIME_TO_SLEEP | NUMBER_OF_PHILOSOPHER_MUST_EAT ]");
        exit(0);
    }

    t_philo *philosopher;
    philosopher = NULL;
    philosopher = init(ag);
    init_mutex(philosopher);
    do_stuff(philosopher);
    waiting_threads(philosopher);
    destroy_mutex(philosopher);
}