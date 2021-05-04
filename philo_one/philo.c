#include "philosophers.h"

void print_operation(t_philo *philo, long time, int op)
{
    int i;

    pthread_mutex_lock(&philo->print);
    if (op == 1)
        printf("\e[1;34m %ld ms Philosopher %d is eating\n", get_current() - philo->start, philo->name);
    if (op == 2)
        printf("\e[0;32m %d ms Philosopher %d has taking a fork\n", get_current() - philo->start, philo->name);
    if (op == 4)
        printf("\e[0;35m %ld ms Philosopher %d is sleeping\n", get_current() - philo->start, philo->name);
    if (op == 5)
        printf("\e[0;36m %ld ms Philosopher %d is thinking\n", get_current() - philo->start, philo->name);
    if (op == 6)
        printf("\e[0;33m %ld ms %d is die\n", get_current() - philo->start, philo->name);
    pthread_mutex_unlock(&philo->print);
}

void *is_dead(t_philo *philo)
{
    int check = -1;
    int i = 0;

    check = philo->time_to_die - (philo->time_to_eat + philo->time_to_sleep);
    if (philo->time_to_die / philo->number_phil < 100)
        check = -1;
    while (1)
    {
        pthread_mutex_lock(philo->died);
        if (philo->num_to_eat != -1)
        {
            if (philo->num_to_eat == philo->done && !i)
            {
                *(philo->finish) += 1;
                i = 1;
            }
            if (*(philo->finish) == philo->number_phil)
            {
                pthread_mutex_lock(philo->mtx);
                printf("\tSimulation stop all philosophers eat %i", philo->num_to_eat);
                pthread_mutex_unlock(philo->loop);
                break;
            }
        }
        if (get_current() - (philo->last_time_eat) >= philo->time_to_die && check <= 0)
        {
            pthread_mutex_lock(philo->mtx);
            print_operation(philo, get_current() - (philo->last_time_eat), 6);
            pthread_mutex_unlock(philo->loop);
            break;
        }
        pthread_mutex_unlock(philo->died);
        usleep(100);
    }
}

void get_fork(t_philo *philo)
{
    pthread_mutex_lock(&philo->forks[philo->right_fork]);
    pthread_mutex_lock(&philo->forks[philo->left_fork]);
    print_operation(philo, get_current() - philo->start, 2);
    print_operation(philo, get_current() - philo->start, 2);
}

void start_eating(t_philo *philo)
{
    print_operation(philo, get_current() - philo->start, 1);
    philo->last_time_eat = get_current();
    philo->done++;
    usleep(philo->time_to_eat * 1000);
}

void end_eating(t_philo *philo)
{
    pthread_mutex_unlock(&philo->forks[philo->right_fork]);
    pthread_mutex_unlock(&philo->forks[philo->left_fork]);
    print_operation(philo, get_current() - philo->start, 4);
    usleep(philo->time_to_sleep * 1000);
    printf("\e[0;35m %ld ms Philosopher %d is thinking\n", get_current() - philo->start, philo->name);
    print_operation(philo, get_current() - philo->start, 5);
}

void *func(void *val)
{
    t_philo *philo;
    pthread_t thr;

    philo = (t_philo *)val;
    pthread_create(&thr, NULL, (void *)is_dead, (void *)philo);
    pthread_detach(thr);
    while (1)
    {
        get_fork(philo);
        start_eating(philo);
        end_eating(philo);
        usleep(10);
    }
    return (val);
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
    pthread_mutex_init(philo->died, NULL);
    pthread_mutex_init(philo->loop, NULL);
    pthread_mutex_init(philo->mtx, NULL);
}

void do_stuff(t_philosophers *philo)
{
    int i;
    pthread_t pth;
    t_philo *philosophers;

    pthread_mutex_lock(philo->loop);
    (philo->finish) = 0;
    i = 0;
    while (i < philo->number_phil)
    {
        philosophers = philo->philo[i];
        philosophers->forks = philo->forks;
        philosophers->died = philo->died;
        philosophers->loop = philo->loop;
        philo->philo[i]->finish = &(philo->finish);
        philosophers->print = philo->print;
        philosophers->mtx = philo->mtx;
        pthread_create(&pth, NULL, (void *)func, (void *)philosophers);
        pthread_detach(pth);
        i++;
    }
    pthread_mutex_lock(philo->loop);
    usleep(100);
    pthread_mutex_unlock(philo->loop);
    pthread_mutex_unlock(philo->mtx);
}

void destroy_mutex(t_philosophers *philo)
{
    int i;

    i = 0;
    pthread_mutex_destroy(philo->died);
    pthread_mutex_destroy(philo->loop);
    pthread_mutex_destroy(philo->mtx);
    while (i < philo->number_phil)
    {
        pthread_mutex_destroy(&philo->forks[i]);
        i++;
    }
}

void clean_leaks(t_philosophers *philo)
{
    int i;

    i = 0;
    while (i < philo->number_phil)
    {
        free(philo->philo[i]);
        i++;
    }
    free(philo->mtx);
    free(philo->died);
    free(philo->loop);
    free(philo->philo);
    free(philo);
}

int main(int ac, char **ag)
{
    t_philosophers *philosopher;

    if (ac < 5 || ac > 6)
    {
        printf("ARGS : [ NUMBER_OF_PHIL | TIME_TO_DIE | TIME_TO_EAT | TIME_TO_SLEEP | NUMBER_OF_PHILOSOPHER_MUST_EAT ]");
        exit(0);
    }

    philosopher = NULL;
    philosopher = init(ag);
    init_mutex(philosopher);
    do_stuff(philosopher);
    destroy_mutex(philosopher);
    clean_leaks(philosopher);
    return (0);
}