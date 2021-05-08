#include "philo.h"

void	check_done(t_philosophers	*philo)
{
	pthread_t	pth;

	if (philo->num_to_eat != -1)
	{
		pthread_create(&pth, NULL, (void *)check_eat, (void *)philo);
		pthread_detach(pth);
	}
}

void	finishing(t_philosophers *philo)
{
	sem_wait(philo->loop);
	destroy_sem(philo);
	exit(0);
}

void	do_stuff(t_philosophers *philo)
{
	      int	i;
	pthread_t	pth;
	  t_philo	*philosophers;
	    pid_t	f;

	i = 0;
	sem_wait(philo->loop);
	check_done(philo);
	while (i < philo->number_phil)
	{
		f = fork();
		if (f == 0)
		{
			philosophers = philo->philo[i];
			philosophers->forks = philo->forks;
			philosophers->died = philo->died;
			philosophers->loop = philo->loop;
			philosophers->print = philo->print;
			philosophers->mtx = philo->mtx;
			func(philosophers);
			exit(0);
		}
		i++;
	}
	finishing(philo);
}
