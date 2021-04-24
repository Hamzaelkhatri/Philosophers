#include "philosophers.h"

long get_current()
{
   	struct timeval	current;
	gettimeofday(&current, NULL);
	return (current.tv_sec * 1000L + current.tv_usec / 1000L);

}

t_philo * init(char **arg)
{
    t_philo *philosopher;

    philosopher = malloc(sizeof(t_philo));
    if(!philosopher)
        exit(1);
    philosopher->Philosophers = malloc(sizeof(pthread_t) * ft_atoi(arg[1]));
    if(!philosopher->Philosophers)
        exit(1);
    philosopher->forks = malloc(sizeof(pthread_mutex_t) * ft_atoi(arg[1]));
    if(!philosopher->forks)
        exit(1);
    philosopher->state = malloc(sizeof(pthread_t) * ft_atoi(arg[1]));
    if(!philosopher->state)
        exit(1);
    philosopher->time_to_die = ft_atoi(arg[2]);
    philosopher->time_to_eat = ft_atoi(arg[3]);
    philosopher->time_to_sleep = ft_atoi(arg[4]);
    if(arg[5])
        philosopher->number_time_to_eat = ft_atoi(arg[5]);
    philosopher->current_time = get_current();
    philosopher->number_phil = ft_atoi(arg[1]);
    philosopher->index_of_phil = 0;

    return (philosopher);
}