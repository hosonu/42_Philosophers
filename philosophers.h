#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>


typedef struct s_philos
{
	struct s_data_arg	*data;
	pthread_t	threads;
	int			no;
	int			eat_cnt;
	int			status;
	int			is_eating;
	int			time_of_death;
	pthread_mutex_t	mutex;
	pthread_mutex_t	*right_fk;
	pthread_mutex_t	*left_fk;
}	t_philos;

typedef struct s_data_arg
{
	pthread_t	*thread;
	t_philos	*philos;
	pthread_mutex_t	*forks;
	int	start;
	int	num_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	num_must_eat;
	int death;
	int fin;
	pthread_mutex_t	mutex;
	pthread_mutex_t	mutex_for_wrt;
}	t_data_arg;

//init_data.c
int	init_data(t_data_arg *data, int argc, char **argv);

//excute_threads.c
int	excute_threads(t_data_arg *data);

//philo_actions
void	doing_something(t_philos *philo);
void	write_actions(char *str, t_philos *philo);

//philo_utils.c
int	x_gettimeofday(void);
int	x_usleep(useconds_t time);
int     ft_atoi(const char *str);
int	ft_strcmp(char *s1, char *s2);

#endif
