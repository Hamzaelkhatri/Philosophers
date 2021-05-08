#include "philo.h"

void	print_operation(t_philo *philo, long time, int op)
{
	sem_wait(philo->print);
	if (op == 1)
		printf("\e[1;34m %ld ms Philosopher %d is eating\n",
			get_current() - philo->start, philo->name);
	if (op == 2)
		printf("\e[0;32m %ld ms Philosopher %d has taking a fork\n",
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
	sem_post(philo->print);
}

int	check_die(t_philo *philo, int check)
{
	if (get_current()- (philo->last_time_eat) >= philo->time_to_die
		&& check <= 0)
		return (0);
	return (1);
}
