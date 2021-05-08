#include "philo.h"

void	*is_dead(t_philo *philo)
{
	int	check;

	check = philo->time_to_die - (philo->time_to_eat + philo->time_to_sleep);
	if (philo->time_to_die / philo->number_phil < 100)
		check = -1;
	while (1)
	{
		if (!check_die(philo, check))
		{
			sem_wait(philo->print);
			printf("\e[0;33m %ld ms %d is die\n",
				get_current() - philo->start, philo->name);
			sem_post(philo->loop);
			usleep(400);
			sem_post(philo->died);
			exit(0);
		}
		sem_post(philo->died);
	}
	return (NULL);
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
	free(philo->philo);
	free(philo);
}

void	check_eat(void *philosophers)
{
	t_philosophers	*philo;
	           int	j;

	j = 0;
	philo = (t_philosophers *)philosophers;
	while (1)
	{
		sem_wait(philo->mtx);
		if (j <= philo->number_phil * philo->num_to_eat + philo->num_to_eat)
			j++;
		else
		{
			sem_wait(philo->print);
			printf("Simulation stop all philo eat %i at", philo->num_to_eat);
			sem_post(philo->loop);
			clean_leaks(philo);
			exit(0);
		}
	}
}

int	main(int ac, char **ag)
{
	t_philosophers	*philosopher;

	check_args(ac, ag);
	philosopher = NULL;
	philosopher = init(ag);
	init_mutex(philosopher);
	do_stuff(philosopher);
	return (0);
}
