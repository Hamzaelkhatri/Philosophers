#include "philo.h"

void	start_eating(t_philo *philo)
{
	print_operation(philo, get_current() - philo->start, 1);
	philo->last_time_eat = get_current();
	philo->done++;
	usleep(philo->time_to_eat * 1000);
}

void	end_eating(t_philo *philo)
{
	sem_post(philo->forks);
	sem_post(philo->forks);
	print_operation(philo, get_current() - philo->start, 4);
	usleep(philo->time_to_sleep * 1000);
	printf("\e[0;35m %ld ms Philosopher %d is thinking\n",
		get_current() - philo->start, philo->name);
	print_operation(philo, get_current() - philo->start, 5);
}
