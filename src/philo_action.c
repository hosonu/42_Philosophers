#include "../philosophers.h"

void	write_actions(char *str, t_philos *philo)
{
	// unsigned int	time;

	pthread_mutex_lock(&philo->data->mutex_for_wrt);
	// time = x_gettimeofday() - philo->data->start;
	if(ft_strcmp("died", str) == 0 && philo->data->death == 0)
	{
		printf("death\n");
		philo->data->death = 1;
	}
	if(philo->data->death == 0)
		printf("now %s\n", str);
	pthread_mutex_unlock(&philo->data->mutex_for_wrt);
}

void	doing_something(t_philos *philo)
{
	pthread_mutex_lock(philo->right_fk);
	write_actions("take right", philo);
	pthread_mutex_lock(philo->left_fk);
	write_actions("take left", philo);
	pthread_mutex_lock(&philo->mutex);
	philo->is_eating = 1;
	philo->time_of_death = x_gettimeofday() + philo->data->time_to_die;
	write_actions("eating", philo);
	philo->eat_cnt++;
	x_usleep(philo->data->time_to_eat);
	philo->is_eating = 0;
	pthread_mutex_unlock(&philo->mutex);
	pthread_mutex_unlock(philo->right_fk);
	pthread_mutex_unlock(philo->left_fk);
	write_actions("sleeping", philo);
	x_usleep(philo->data->time_to_sleep);
}