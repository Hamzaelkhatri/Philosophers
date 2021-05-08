#include "philosophers.h"

void	finish_done(t_philo *philo)
{
	pthread_mutex_lock(philo->mtx);
	printf("Simulation stop all philo eat %i", philo->num_to_eat);
	pthread_mutex_unlock(philo->loop);
}

void	finish_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->mtx);
	print_operation(philo, get_current() - (philo->last_time_eat), 6);
	pthread_mutex_unlock(philo->loop);
}

int	check_die(t_philo *philo, int check)
{
	if (get_current()- (philo->last_time_eat) >= philo->time_to_die
		&& check <= 0)
		return (0);
	return (1);
}

void	affect_check(t_philo *philo, int *check)
{
	*check = philo->time_to_die - (philo->time_to_eat + philo->time_to_sleep);
	if (philo->time_to_die / philo->number_phil < 100)
		*check = -1;
}
