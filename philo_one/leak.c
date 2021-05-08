#include "philosophers.h"

void	destroy_mutex(t_philosophers *philo)
{
	int	i;

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

void	clean_leaks(t_philosophers *philo)
{
	int	i;

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
