#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <sys/stat.h>

typedef struct s_philo
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	*died;
	pthread_mutex_t	print;
	pthread_mutex_t	*mtx;
	pthread_mutex_t	*loop;
	long			start;
	int				*finish;
	long			last_time_eat;
	int				left_fork;
	int				right_fork;
	int				name;
	int				done;
	long			time_to_die;
	long			time_to_eat;
	int				check_die;
	long			time_to_sleep;
	long			number_time_to_eat;
	int				number_phil;
	int				num_to_eat;
}					t_philo;

typedef struct s_philosophers
{
	pthread_mutex_t		*died;
	pthread_mutex_t		print;
	pthread_mutex_t		*forks;
	pthread_mutex_t		*mtx;
	pthread_mutex_t		*loop;
	int					finish;
	int					done;
	int					num_to_eat;
	long				time_to_die;
	long				time_to_eat;
	int					number_phil;
	long				time_to_sleep;
	int					check_died;
	t_philo				**philo;
}						t_philosophers;

long long				ft_atoi(const char *str);
long					get_current(void);
char					*ft_itoa(long long n);
t_philosophers			*init(char **arg);
void					init_mutex(t_philosophers *philo);
void					print_operation(t_philo *philo, long time, int op);
void					get_fork(t_philo *philo);
void					start_eating(t_philo *philo);
void					end_eating(t_philo *philo);
void					destroy_mutex(t_philosophers *philo);
void					clean_leaks(t_philosophers *philo);
void					check_args(int ac, char **av);
void					finish_done(t_philo *philo);
void					finish_dead(t_philo *philo);
int						check_die(t_philo *philo, int check);
void					affect_check(t_philo *philo, int *check);

#endif