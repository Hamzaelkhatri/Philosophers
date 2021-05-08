#include "philo.h"

void	clean_leaks(t_philosophers *philo)
{
	int	i;

	i = 0;
	while (i < philo->number_phil)
	{
		free(philo->philo[i]);
		i++;
	}
	free(philo->died);
	free(philo->loop);
	free(philo->philo);
	free(philo);
}
