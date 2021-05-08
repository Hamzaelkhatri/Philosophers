#include "philo.h"

void	get_fork(t_philo *philo)
{
	sem_wait(philo->forks);
	sem_wait(philo->forks);
	print_operation(philo, get_current() - philo->start, 2);
	print_operation(philo, get_current() - philo->start, 2);
}

void	start_eating(t_philo *philo)
{
	print_operation(philo, get_current() - philo->start, 1);
	philo->last_time_eat = get_current();
	if (philo->num_to_eat != -1)
		sem_post(philo->mtx);
	philo->done++;
	usleep(philo->time_to_eat * 1000);
}

void	end_eating(t_philo *philo)
{
	sem_post(philo->forks);
	sem_post(philo->forks);
	print_operation(philo, get_current() - philo->start, 4);
	usleep(philo->time_to_sleep * 1000);
	print_operation(philo, get_current() - philo->start, 5);
}

void	*func(void *val)
{
	 t_philo	*philo;
	pthread_t	thr;

	philo = (t_philo *)val;
	pthread_create(&thr, NULL, (void *)is_dead, (void *)philo);
	pthread_detach(thr);
	while (1)
	{
		get_fork(philo);
		start_eating(philo);
		end_eating(philo);
	}
	return (val);
}
