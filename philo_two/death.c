#include "philo.h"

void	affect_check(t_philo *philo, int *check)
{
	*check = philo->time_to_die - (philo->time_to_eat + philo->time_to_sleep);
	if (philo->time_to_die / philo->number_phil < 100)
		*check = -1;
}

int	check_die(t_philo *philo, int check)
{
	if (get_current()- (philo->last_time_eat) >= philo->time_to_die
		&& check <= 0)
		return (0);
	return (1);
}

int	is_dead2(t_philo *philo, int *i)
{
	if (philo->num_to_eat == philo->done && !(*i))
	{
		*(philo->finish) += 1;
		*i = 1;
	}
}

void	affect_stop(t_philo *philo)
{
	sem_wait(philo->print);
	printf("Simulation stop all philo eat %i", philo->num_to_eat);
	sem_post(philo->loop);
	usleep(400);
	sem_post(philo->died);
}

void	affect_die(t_philo *philo)
{
	sem_wait(philo->print);
	printf("\e[0;33m %ld ms %d is die\n",
		get_current() - philo->start, philo->name);
	sem_post(philo->loop);
	usleep(400);
	sem_post(philo->died);
}
