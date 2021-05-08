#include "philo.h"

void	destroy_sem(t_philosophers *philo)
{
	sem_close(philo->died);
	sem_close(philo->loop);
	sem_close(philo->forks);
}

void	init_mutex(t_philosophers *philo)
{
	sem_unlink("/fork");
	sem_unlink("/print");
	sem_unlink("/died");
	sem_unlink("/loop");
	sem_unlink("/mtx");
	philo->forks = sem_open("/fork", O_CREAT, 0777, philo->number_phil);
	philo->print = sem_open("/print", O_CREAT, 0777, 1);
	philo->died = sem_open("/died", O_CREAT, 0777, 1);
	philo->loop = sem_open("/loop", O_CREAT, 0777, 1);
}

long	get_current(void)
{
	struct timeval	current;

	gettimeofday(&current, NULL);
	return (current.tv_sec * 1000 + current.tv_usec / 1000);
}

void	init_each(t_philosophers *philo)
{
	int	i;

	i = 0;
	while (i < philo->number_phil)
	{
		philo->philo[i] = malloc(sizeof(t_philo));
		philo->philo[i]->right_fork = i;
		philo->philo[i]->left_fork = (i + 1) % philo->number_phil;
		philo->philo[i]->last_time_eat = get_current();
		philo->philo[i]->start = get_current();
		philo->philo[i]->number_phil = philo->number_phil;
		philo->philo[i]->name = i + 1;
		philo->philo[i]->time_to_eat = philo->time_to_eat;
		philo->philo[i]->done = 0;
		philo->philo[i]->check_die = 0;
		philo->philo[i]->num_to_eat = philo->num_to_eat;
		philo->philo[i]->time_to_die = philo->time_to_die;
		philo->philo[i]->time_to_sleep = philo->time_to_sleep;
		i++;
	}
}

t_philosophers	*init(char **arg)
{
	t_philosophers	*philo;
	           int	i;

	i = 0;
	philo = malloc(sizeof(t_philosophers));
	philo->number_phil = ft_atoi(arg[1]);
	philo->philo = malloc(sizeof(t_philo) * ft_atoi(arg[1]));
	philo->forks = malloc(sizeof(pthread_mutex_t) * ft_atoi(arg[1]));
	philo->time_to_die = ft_atoi(arg[2]);
	philo->time_to_eat = ft_atoi(arg[3]);
	philo->time_to_sleep = ft_atoi(arg[4]);
	philo->num_to_eat = -1;
	if (arg[5])
		philo->num_to_eat = ft_atoi(arg[5]);
	philo->check_died = 0;
	init_each(philo);
	return (philo);
}
