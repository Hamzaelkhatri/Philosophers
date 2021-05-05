#ifndef PHILO_H
#define PHILO_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <sys/time.h>
#include <fcntl.h>

typedef struct s_philo
{
    sem_t *forks;
    sem_t *died;
    sem_t *print;
    sem_t *mtx;
    sem_t *loop;
    long start;
    int *finish;
    long last_time_eat;
    int left_fork;
    int right_fork;
    int name;
    int done;
    long time_to_die;
    long time_to_eat;
    int check_die;
    long time_to_sleep;
    long number_time_to_eat;
    int number_phil;
    int num_to_eat;
} t_philo;

typedef struct s_philosophers
{
    sem_t *died;
    sem_t *print;
    sem_t *forks;
    sem_t *mtx;
    sem_t *loop;
    int finish;
    int done;
    int num_to_eat;
    long time_to_die;
    long time_to_eat;
    int number_phil;
    long time_to_sleep;
    int check_died;
    t_philo **philo;
} t_philosophers;

long long ft_atoi(const char *str);
long get_current();
char *ft_itoa(long long n);
t_philosophers *init(char **arg);

#endif