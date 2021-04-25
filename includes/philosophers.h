#ifndef PHILOSPHERS_H
# define PHILOSPHERS_H
# define EAT '1'
# define NOT_EAT '0'
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>

typedef struct s_times
{
    int index;
    long last_time_eat;
}s_times;

typedef struct s_philo
{
    pthread_mutex_t *forks;
    pthread_t *Philosophers;
    char    **last_time_eat;
    long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
    long    current_time;
    int     number_phil;
    int     index_of_phil;
	long	number_time_to_eat;
    char *state;
}t_philo;

long long	ft_atoi(const char *str);
long get_current();
char	*ft_itoa(long long n);
t_philo *init(char **arg);

#endif