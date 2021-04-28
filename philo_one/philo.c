#include "philosophers.h"

void *is_dead(t_philo *philo)
{
    int i;

    i = -100;
    // puts("he is checking...");
    if (get_current() - philo->times[philo->index_of_phil]->last_time_eat > philo->time_to_die)
    {
        pthread_mutex_lock(&philo->died);
        printf("\e[0;33m %ld ms %d is die :(\n", get_current() - philo->times[philo->index_of_phil]->start, philo->index_of_phil);
        exit(0);
    }
    else
    {
        pthread_mutex_unlock(&philo->died);
    }
    printf("\e[0;33m [checking for %i---> %i]\n", philo->index_of_phil, i);
    // while (i < philo->number_phil)
    // {
    //     if (get_current() - philo->times[i]->last_time_eat > philo->time_to_die)
    //     {
    //         printf("\e[0;33m %ld ms %d is die :(\n", get_current() - philo->current_time, i);
    //         exit(1);
    //     }
    //     usleep(20);
    //     i++;
    // }
}

void *func(void *val)
{
    t_philo *philo;
    pthread_t checker;
    int i;
    int j;

    philo = (t_philo *)val;

    philo = (t_philo *)val;
    pthread_create(&checker, NULL, (void *)is_dead, (void *)philo);
    pthread_detach(checker);
    while (1)
    {
        j = 0;
        i = philo->index_of_phil;
        if (philo->state[i] == NAN || philo->state[i] == THINKING || philo->state[i] == SLEEPING)
        {
            printf("\e[0;31m %d ms Philosopher %d is thinking\n", get_current() - philo->times[i]->start, i);
            philo->state[i] = THINKING;
        }
        if (!pthread_mutex_lock(&philo->forks[i]))
        {
            printf("\e[0;32m %d ms Philosopher %d has taking a fork 1\n", get_current() - philo->times[i]->start, i);
            // is_dead(philo);
            j++;
        }
        if (!pthread_mutex_lock(&philo->forks[(i + 1) % philo->number_phil]))
        {
            printf("\e[0;32m %ld ms Philosopher %d has taking a fork 2\n", get_current() - philo->times[i]->start, i);
            j++;
            // is_dead(philo);
            // usleep(20);
        }
        if (j == 2)
        {
            printf("\e[1;34m %ld ms Philosopher %d is eating\n", get_current() - philo->times[i]->start, i);
            philo->state[i] = EAT;
            usleep(philo->time_to_eat * 1000);
            philo->times[i]->last_time_eat = get_current();
            pthread_mutex_unlock(&philo->forks[i]);
            pthread_mutex_unlock(&philo->forks[(i + 1) % philo->number_phil]);
            printf("\e[0;35m %ld ms Philosopher %d is sleeping\n", get_current() - philo->times[i]->start, i);
            philo->state[i] = SLEEPING;
            usleep(philo->time_to_sleep * 1000);
            philo->state[i] = NAN;
            j = 0;
        }
        sleep(100);
        if (get_current() - philo->times[i]->last_time_eat > philo->time_to_die)
        {
            pthread_mutex_lock(&philo->died);
            break;
        }
    }
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
    pthread_mutex_init(&philo->died, NULL);
}

void do_stuff(t_philo *philo)
{
    int i;

    // pthread_create(&philo->Philosophers, NULL, (void *)is_dead, (void *)philo);
    // pthread_detach(philo->Philosophers);
    i = 0;
    while (i < philo->number_phil)
    {
        pthread_create(&philo->Philosophers, NULL, (void *)func, (void *)philo);
        philo->index_of_phil = i;
        i++;
        usleep(20);
    }
    i = 0;
}

void waiting_threads(t_philo *philo)
{
    int i;

    i = 0;
    while (i < philo->number_phil)
    {
        pthread_join(philo->Philosophers, NULL);
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