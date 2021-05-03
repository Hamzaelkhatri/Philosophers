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

typedef struct s_philo
{
    pthread_mutex_t *forks;
    pthread_mutex_t *died;
    pthread_mutex_t print;
    pthread_mutex_t *mtx;
    pthread_mutex_t *loop;
    long start;
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
    pthread_mutex_t *died;
    pthread_mutex_t print;
    pthread_mutex_t *forks;
    pthread_mutex_t *mtx;
    pthread_mutex_t *loop;
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