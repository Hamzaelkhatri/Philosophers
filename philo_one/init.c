#include "philosophers.h"

void	init_mutex(t_philosophers *philo)
{
	int	i;

	i = 0;
	philo->loop = malloc(sizeof(pthread_mutex_t));
	philo->died = malloc(sizeof(pthread_mutex_t));
	philo->mtx = malloc(sizeof(pthread_mutex_t));
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

long	get_current(void)
{
	struct timeval	current;

	gettimeofday(&current, NULL);
	return (current.tv_sec * 1000 + current.tv_usec / 1000);
}

void	init_each(t_philosophers *philo)
{
	int	i;

	i = 0;
	while (i < philo->number_phil)
	{
		philo->philo[i] = malloc(sizeof(t_philo));
		philo->philo[i]->right_fork = i;
		philo->philo[i]->left_fork = (i + 1) % philo->number_phil;
		philo->philo[i]->last_time_eat = get_current();
		philo->philo[i]->start = get_current();
		philo->philo[i]->number_phil = philo->number_phil;
		philo->philo[i]->name = i + 1;
		philo->philo[i]->time_to_eat = philo->time_to_eat;
		philo->philo[i]->done = 0;
		philo->philo[i]->check_die = 0;
		philo->philo[i]->num_to_eat = philo->num_to_eat;
		philo->philo[i]->time_to_die = philo->time_to_die;
		philo->philo[i]->time_to_sleep = philo->time_to_sleep;
		i++;
	}
}

t_philosophers	*init(char **arg)
{
	t_philosophers	*philo;
	           int	i;

	i = 0;
	philo = malloc(sizeof(t_philosophers));
	philo->number_phil = ft_atoi(arg[1]);
	philo->philo = malloc(sizeof(t_philo) * ft_atoi(arg[1]));
	philo->forks = malloc(sizeof(pthread_mutex_t) * ft_atoi(arg[1]));
	philo->time_to_die = ft_atoi(arg[2]);
	philo->time_to_eat = ft_atoi(arg[3]);
	philo->time_to_sleep = ft_atoi(arg[4]);
	philo->num_to_eat = -1;
	if (arg[5])
		philo->num_to_eat = ft_atoi(arg[5]);
	philo->check_died = 0;
	init_each(philo);
	return (philo);
}
