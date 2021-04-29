#include "philosophers.h"

long get_current()
{
    struct timeval current;
    gettimeofday(&current, NULL);
    return (current.tv_sec * 1000 + current.tv_usec / 1000);
}

t_philo *init(char **arg)
{
    t_philo *philosopher;
    int i;

    philosopher = malloc(sizeof(t_philo));
    if (!philosopher)
        exit(1);
    philosopher->check_died = 0;
    philosopher->forks = malloc(sizeof(pthread_mutex_t) * ft_atoi(arg[1]));
    if (!philosopher->forks)
        exit(1);
    philosopher->state = malloc(sizeof(pthread_t) * ft_atoi(arg[1]) + 1);
    if (!philosopher->state)
        exit(1);
    i = 0;
    philosopher->number_phil = ft_atoi(arg[1]);
    while (i < philosopher->number_phil)
    {
        philosopher->state[i] = NAN;
        i++;
    }
    philosopher->state[i] = '\0';
    philosopher->times = (t_times **)malloc(sizeof(t_times *) * philosopher->number_phil);
    i = 0;
    while (i < philosopher->number_phil)
    {
        philosopher->times[i] = malloc(sizeof(t_times));
        philosopher->times[i]->last_time_eat = get_current();
        philosopher->times[i]->start = get_current();
        philosopher->times[i]->last = 0;
        i++;
    }
    philosopher->times[i - 1]->last = 1;
    philosopher->time_to_die = ft_atoi(arg[2]);
    philosopher->time_to_eat = ft_atoi(arg[3]);
    philosopher->time_to_sleep = ft_atoi(arg[4]);
    if (arg[5])
        philosopher->number_time_to_eat = ft_atoi(arg[5]);
    philosopher->index_of_phil = 0;
    return (philosopher);
}