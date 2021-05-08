#include "philosophers.h"

int	is_dead2(t_philo *philo, int *i)
{
	if (philo->num_to_eat == philo->done && !(*i))
	{
		*(philo->finish) += 1;
		*i = 1;
	}
}

void	*is_dead(t_philo *philo)
{
	int	check;
	int	i;

	i = 0;
	affect_check(philo, &check);
	while (1)
	{
		pthread_mutex_lock(philo->died);
		if (philo->num_to_eat != -1)
		{
			is_dead2(philo, &i);
			if (*(philo->finish) == philo->number_phil)
			{
				finish_done(philo);
				break ;
			}
		}
		if (!check_die(philo, check))
		{
			finish_dead(philo);
			break ;
		}
		pthread_mutex_unlock(philo->died);
	}
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
		usleep(10);
	}
	return (val);
}

void	do_stuff(t_philosophers *philo)
{
	      int	i;
	pthread_t	pth;
	  t_philo	*philosophers;

	pthread_mutex_lock(philo->loop);
	(philo->finish) = 0;
	i = 0;
	while (i < philo->number_phil)
	{
		philosophers = philo->philo[i];
		philosophers->forks = philo->forks;
		philosophers->died = philo->died;
		philosophers->loop = philo->loop;
		philo->philo[i]->finish = &(philo->finish);
		philosophers->print = philo->print;
		philosophers->mtx = philo->mtx;
		pthread_create(&pth, NULL, (void *)func, (void *)philosophers);
		pthread_detach(pth);
		i++;
	}
	pthread_mutex_lock(philo->loop);
	usleep(100);
	pthread_mutex_unlock(philo->loop);
	pthread_mutex_unlock(philo->mtx);
}

int	main(int ac, char **ag)
{
	t_philosophers	*philosopher;

	philosopher = NULL;
	philosopher = init(ag);
	init_mutex(philosopher);
	do_stuff(philosopher);
	destroy_mutex(philosopher);
	clean_leaks(philosopher);
	return (0);
}
