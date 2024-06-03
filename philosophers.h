#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philos
{
	struct s_philos		*next;
	pthread_mutex_t		*left_fk;
	pthread_mutex_t		*right_fk;
	struct s_data_arg	*data;
	pthread_t			thread;
	int					no;
	int					eat_cnt;
	int					is_dead;
	int					is_eating;
	int					dissolution;
	long				time_after_ate;
	long				start;
	pthread_mutex_t		eat_mutex;
	pthread_mutex_t		death_mutex;
	pthread_mutex_t		dissolute_mtx;
	pthread_mutex_t		*wrt_mtx;
}	t_philos;

typedef struct s_data_arg
{
	long			num_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			num_must_eat;
	t_philos		*philo;
}	t_data_arg;

//init_data.c
int		init_data(t_data_arg *data, char *argv[]);

//excute_thread.c
int		excute_thread(t_philos *philo);

//action.c
void	action_philo(t_philos *philo);

//ft_funcs.c
int		x_gettimeofday(void);
int		x_usleep(useconds_t time);
long	ft_atol(const char *str);
int		ft_strcmp(char *s1, char *s2);

//observe.c
void	*observe_philo(void *data);

//philo_utils.c
long	get_elapsedtime(long start_time);
void	do_write(t_philos *philo, char *state);


#endif
