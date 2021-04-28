#ifndef PHILOSPHERS_H
#define PHILOSPHERS_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>
#define EAT '1'
#define NAN '0'
#define SLEEPING '2'
#define THINKING '3'

typedef struct s_times
{
    long start;
    long last_time_eat;
} t_times;

typedef struct s_philo
{
    pthread_mutex_t *forks;
    pthread_mutex_t died;
    pthread_t Philosophers;
    t_times **times;
    long time_to_die;
    long time_to_eat;
    long time_to_sleep;
    int number_phil;
    int index_of_phil;
    long number_time_to_eat;
    char *state;
} t_philo;

long long ft_atoi(const char *str);
long get_current();
char *ft_itoa(long long n);
t_philo *init(char **arg);

#endif