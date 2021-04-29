#include "philosophers.h"

void print_operation(t_philo *philo, int op)
{
    int i;

    i = philo->index_of_phil;
    if (pthread_mutex_lock(&philo->times[i]->print) < 0)
        exit(1);
    if (op == 1)
        printf("\e[1;34m %ld ms Philosopher %d is eating\n", get_current() - philo->times[i]->start, i);
    if (op == 2)
    {
        printf("\e[0;32m %d ms Philosopher %d has taking a fork 1\n", get_current() - philo->times[i]->start, i);
    }
    if (op == 3)
    {
        printf("\e[0;32m %ld ms Philosopher %d has taking a fork 2\n", get_current() - philo->times[i]->start, i);
    }
    if (op == 4)
    {
        printf("\e[0;35m %ld ms Philosopher %d is sleeping\n", get_current() - philo->times[i]->start, i);
    }
    if (op == 5)
    {
        printf("\e[0;36m %ld ms Philosopher %d is thinking\n", get_current() - philo->times[i]->start, i);
    }
    if (op == 6)
    {
        printf("\e[0;33m %ld ms %d is die\n", get_current() - philo->times[i]->start, philo->index_of_phil);
    }
    pthread_mutex_unlock(&philo->times[i]->print);
}

void *is_dead(t_philo *philo)
{
    int i;
    long time;

    i = philo->index_of_phil;
    while (philo->check_died != 1)
    {
        time = get_current();
        if (time - philo->times[i]->last_time_eat > philo->time_to_die)
        {
            philo->check_died = 1;
            print_operation(philo, 6);
            pthread_mutex_unlock(&philo->died);
            exit(0);
            // break;
        }
        usleep(100);
    }
}

void get_fork(t_philo *philo)
{
    int i;

    i = philo->index_of_phil;
    pthread_mutex_lock(&philo->forks[i]);
    print_operation(philo, 2);
    pthread_mutex_lock(&philo->forks[(i + 1) % philo->number_phil]);
    print_operation(philo, 3);
}

void start_eating(t_philo *philo)
{
    int i;

    i = philo->index_of_phil;
    print_operation(philo, 1);
    usleep(philo->time_to_eat * 1000);
    philo->times[i]->last_time_eat = get_current();
}

void end_eating(t_philo *philo)
{
    int i;

    i = philo->index_of_phil;
    pthread_mutex_unlock(&philo->forks[i]);
    pthread_mutex_unlock(&philo->forks[(i + 1) % philo->number_phil]);
    print_operation(philo, 4);
    usleep(philo->time_to_sleep * 1000);
    print_operation(philo, 5);
}

void *func(void *val)
{
    t_philo *philo;
    pthread_t checker;
    int i;

    philo = (t_philo *)val;
    pthread_create(&checker, NULL, (void *)is_dead, (void *)philo);
    pthread_detach(checker);
    while (1)
    {
        get_fork(philo);
        start_eating(philo);
        end_eating(philo);
        // if (philo->index_of_phil == philo->number_phil - 1)
        // {
        // philo->index_of_phil = 0;
        // }
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
        pthread_mutex_init(&philo->times[i]->print, NULL);
        i++;
    }
    pthread_mutex_init(&philo->died, NULL);
}

void do_stuff(t_philo *philo)
{
    int i;

    i = 0;
    pthread_mutex_lock(&philo->died);
    while (i < philo->number_phil)
    {
        pthread_create(&philo->Philosophers, NULL, (void *)func, (void *)philo);
        pthread_detach(philo->Philosophers);
        philo->index_of_phil = i;
        usleep(100);
        i++;
    }
    i = 0;
}

void waiting_threads(t_philo *philo)
{
    int i;

    i = 0;
    while (i < philo->number_phil)
    {
        // pthread_join(philo->Philosophers, NULL);
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
    while (1)
    {
        /* code */
    }

    destroy_mutex(philosopher);
}