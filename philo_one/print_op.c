#include "philosophers.h"

void	print_operation(t_philo *philo, long time, int op)
{
	int	i;

	pthread_mutex_lock(&philo->print);
	if (op == 1)
		printf("\e[1;34m %ld ms Philosopher %d is eating\n",
			get_current() - philo->start, philo->name);
	if (op == 2)
		printf("\e[0;32m %d ms Philosopher %d has taking a fork\n",
			get_current() - philo->start, philo->name);
	if (op == 4)
		printf("\e[0;35m %ld ms Philosopher %d is sleeping\n",
			get_current() - philo->start, philo->name);
	if (op == 5)
		printf("\e[0;36m %ld ms Philosopher %d is thinking\n",
			get_current() - philo->start, philo->name);
	if (op == 6)
		printf("\e[0;33m %ld ms %d is die\n",
			get_current() - philo->start, philo->name);
	pthread_mutex_unlock(&philo->print);
}

void	get_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->forks[philo->right_fork]);
	pthread_mutex_lock(&philo->forks[philo->left_fork]);
	print_operation(philo, get_current() - philo->start, 2);
	print_operation(philo, get_current() - philo->start, 2);
}

void	start_eating(t_philo *philo)
{
	print_operation(philo, get_current() - philo->start, 1);
	philo->last_time_eat = get_current();
	philo->done++;
	usleep(philo->time_to_eat * 1000);
}

void	end_eating(t_philo *philo)
{
	pthread_mutex_unlock(&philo->forks[philo->right_fork]);
	pthread_mutex_unlock(&philo->forks[philo->left_fork]);
	print_operation(philo, get_current() - philo->start, 4);
	usleep(philo->time_to_sleep * 1000);
	printf("\e[0;35m %ld ms Philosopher %d is thinking\n",
		get_current() - philo->start, philo->name);
	print_operation(philo, get_current() - philo->start, 5);
}
