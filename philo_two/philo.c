#include "philo.h"

void print_operation(t_philo *philo, long time, int op)
{
    int i;

    sem_wait(philo->print);
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
    sem_post(philo->print);
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
        sem_wait(philo->died);
        if (philo->num_to_eat != -1)
        {
            if (philo->num_to_eat == philo->done && !i)
            {
                *(philo->finish) += 1;
                i = 1;
            }
            if (*(philo->finish) == philo->number_phil)
            {
                // puts("sdadsadsadsadsa");
                sem_wait(philo->mtx);
                printf("\tSimulation stop all philosophers eat %i", philo->num_to_eat);
                sem_post(philo->loop);
                break;
            }
        }
        if (get_current() - (philo->last_time_eat) >= philo->time_to_die && check <= 0)
        {
            puts("bslaaa");
            sem_wait(philo->mtx);
            print_operation(philo, get_current() - (philo->last_time_eat), 6);
            sem_post(philo->loop);
            break;
        }
        sem_post(philo->died);
        // usleep(100);
    }
}

void get_fork(t_philo *philo)
{
    sem_wait(philo->forks);
    sem_wait(philo->forks);
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
    sem_post(philo->forks);
    sem_post(philo->forks);
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
        // usleep(10);
    }
    return (val);
}

void init_mutex(t_philosophers *philo)
{
    sem_unlink("/forks");
    sem_unlink("/prints");
    sem_unlink("/dieds");
    sem_unlink("/loops");
    sem_unlink("/mtxs");
    philo->forks = malloc(sizeof(sem_t));
    philo->forks = sem_open("/forks", O_CREAT, O_RDWR, philo->number_phil);
    philo->print = sem_open("/prints", O_CREAT, O_RDWR, 1);
    philo->died = sem_open("/dieds", O_CREAT, O_RDWR, 1);
    philo->loop = sem_open("/loops", O_CREAT, O_RDWR, 1);
    philo->mtx = sem_open("/mtxs", O_CREAT, O_RDWR, 1);
}

void do_stuff(t_philosophers *philo)
{
    int i;
    pthread_t pth;
    t_philo *philosophers;

    (philo->finish) = 0;
    sem_wait(philo->loop);
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
        if (philo->check_died)
            break;
        // usleep(10);
        i++;
    }
    sem_wait(philo->loop);
    // puts("hii");
    // usleep(100);
    sem_post(philo->loop);
    sem_post(philo->mtx);
}

void destroy_sem(t_philosophers *philo)
{
    int i;

    i = 0;
    sem_close(philo->died);
    sem_close(philo->loop);
    sem_close(philo->mtx);
    sem_close(philo->forks);
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

    // while (1)
    //     ;
    destroy_sem(philosopher);
    // clean_leaks(philosopher);
    return (0);
}