# include "../philosophers.h"

void	*observe_philo(void *data)
{
	t_philos *philo;

	philo = (t_philos *)data;
	while(philo->next)
	{
		pthread_mutex_lock(&philo->mutex);
		if (x_gettimeofday() - philo->time_after_ate > philo->data->time_to_die)
		{
			philo->is_dead = 1;
			pthread_mutex_unlock(&philo->mutex);
			break;
		}
		if (philo->eat_cnt == philo->data->num_must_eat)
		{
			pthread_mutex_unlock(&philo->mutex);
			break;
		}
		pthread_mutex_unlock(&philo->mutex);
		x_usleep(1000);
	}
	return (NULL);
}
