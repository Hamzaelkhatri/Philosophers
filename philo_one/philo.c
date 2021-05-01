#include "philosophers.h"

void print_operation(t_philo *philo, int op)
{
    int i;

    pthread_mutex_lock(&philo->print);
    if (op == 1)
        printf("\e[1;34m %ld ms Philosopher %d is eating\n", get_current() - philo->start, philo->name);
    if (op == 2)
    {
        printf("\e[0;32m %d ms Philosopher %d has taking a fork\n", get_current() - philo->start, philo->name);
    }
    if (op == 4)
    {
        printf("\e[0;35m %ld ms Philosopher %d is sleeping\n", get_current() - philo->start, philo->name);
    }
    if (op == 5)
    {
        printf("\e[0;36m %ld ms Philosopher %d is thinking\n", get_current() - philo->start, philo->name);
    }
    if (op == 6)
    {
        printf("\e[0;33m %ld ms %d is die\n", get_current() - philo->start, philo->name);
    }
    pthread_mutex_unlock(&philo->print);
}

void *is_dead(t_philo *philo)
{
    while (!philo->check_die)
    {
        pthread_mutex_lock(&philo->died);
        usleep(10);
        if (get_current() - philo->last_time_eat > philo->time_to_die)
        {
            // sleep(1);
            usleep(10);
            pthread_mutex_unlock(&philo->died);
            philo->check_die = 1;
            print_operation(philo, 6);
            exit(1);
        }
        pthread_mutex_unlock(&philo->died);
    }
}

void get_fork(t_philo *philo)
{
    int i;
    t_philo *pth;

    pthread_mutex_lock(&philo->forks[philo->right_fork]);
    print_operation(philo, 2);
    pthread_mutex_lock(&philo->forks[philo->left_fork]);
    print_operation(philo, 2);
    usleep(10);
}

void start_eating(t_philo *philo)
{
    print_operation(philo, 1);
    philo->last_time_eat = get_current();
    usleep(philo->time_to_eat * 1000);
}

void end_eating(t_philo *philo)
{
    pthread_mutex_unlock(&philo->forks[philo->left_fork]);
    pthread_mutex_unlock(&philo->forks[philo->right_fork]);
    print_operation(philo, 4);
    usleep(philo->time_to_sleep * 1000);
    printf("\e[0;35m %ld ms Philosopher %d is thinking\n", get_current() - philo->start, philo->name);
    print_operation(philo, 5);
}

void *func(void *val)
{
    t_philo *philo;
    pthread_t thr;
    int i;

    philo = (t_philo *)val;
    pthread_create(&thr, NULL, (void *)is_dead, (void *)philo);
    pthread_detach(thr);
    philo->start = get_current();
    while (1)
    {
        get_fork(philo);
        start_eating(philo);
        end_eating(philo);
    }
    return (val);
}

int check_args(char **ag)
{
    int i = 0;
    while (ag[i])
    {
    }
}

void init_mutex(t_philosophers *philo)
{
    int i;

    i = 0;
    while (i < philo->number_phil)
    {
        pthread_mutex_init(&philo->forks[i], NULL);
        i++;
    }
    pthread_mutex_init(&philo->print, NULL);
    pthread_mutex_init(&philo->died, NULL);
    pthread_mutex_init(&philo->died, NULL);
}

void do_stuff(t_philosophers *philo)
{
    int i;
    pthread_t pth;
    t_philo *philosophers;

    i = 0;
    while (i < philo->number_phil)
    {
        philosophers = philo->philo[i];
        philosophers->forks = philo->forks;
        philosophers->died = philo->died;
        philosophers->print = philo->print;
        pthread_create(&pth, NULL, (void *)func, (void *)philosophers);
        pthread_detach(pth);
        usleep(100);
        i++;
    }
    i = 0;
}

void waiting_threads(void)
{
    int i;

    i = 0;
    while (!i)
        ;
}

void destroy_mutex(t_philosophers *philo)
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

    t_philosophers *philosopher;
    philosopher = NULL;
    philosopher = init(ag);
    init_mutex(philosopher);
    do_stuff(philosopher);
    waiting_threads();
    destroy_mutex(philosopher);
}