# include "../philosophers.h"

void	dissolution_announcement(t_philos *philo)
{
	int i;

	i = 0;
	while(i < philo->data->num_philo)
	{
		philo->dissolution = 1;
		philo = philo->next;
		i++;
	}
}

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
			dissolution_announcement(philo);
			pthread_mutex_unlock(&philo->mutex);
			break;
		}
		if (philo->eat_cnt == philo->data->num_must_eat)
		{
			dissolution_announcement(philo);
			pthread_mutex_unlock(&philo->mutex);
			break;
		}
		pthread_mutex_unlock(&philo->mutex);
		x_usleep(1000);
	}
	return (NULL);
}
