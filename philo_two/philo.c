#include "philo.h"

void	*is_dead(t_philo *philo)
{
	int	check;
	int	i;

	affect_check(philo, &check);
	i = 0;
	while (1)
	{
		sem_wait(philo->died);
		if (philo->num_to_eat != -1)
		{
			is_dead2(philo, &i);
			if (*(philo->finish) == philo->number_phil)
			{
				affect_stop(philo);
				break ;
			}
		}
		if (!check_die(philo, check))
		{
			affect_die(philo);
			break ;
		}
		sem_post(philo->died);
	}
	return (NULL);
}

void	get_fork(t_philo *philo)
{
	sem_wait(philo->forks);
	sem_wait(philo->forks);
	print_operation(philo, get_current() - philo->start, 2);
	print_operation(philo, get_current() - philo->start, 2);
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

void	do_stuff(t_philosophers *philo)
{
	      int	i;
	pthread_t	pth;
	  t_philo	*philosophers;

	(philo->finish) = 0;
	i = 0;
	sem_wait(philo->loop);
	while (i < philo->number_phil)
	{
		philosophers = philo->philo[i];
		philosophers->forks = philo->forks;
		philosophers->died = philo->died;
		philosophers->loop = philo->loop;
		philo->philo[i]->finish = &(philo->finish);
		philosophers->print = philo->print;
		pthread_create(&pth, NULL, (void *)func, (void *)philosophers);
		pthread_detach(pth);
		usleep(100);
		i++;
	}
	sem_wait(philo->loop);
	return ;
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
