# include "../philosophers.h"

int	is_dead(t_philos *philo)
{
	if(philo->is_dead == 1)
	{
		do_write(philo, "death");
		return (1);
	}
	return (0);
}

void	eating_philo(t_philos *philo)
{
	if(philo->no % 2== 0)
	{
		pthread_mutex_lock(philo->left_fk);
		pthread_mutex_lock(philo->right_fk);
	}
	else
	{
		pthread_mutex_lock(philo->right_fk);
		pthread_mutex_lock(philo->left_fk);
	}
	do_write(philo, "fork");
	do_write(philo, "fork");
	do_write(philo, "eat");
	philo->time_after_ate = x_gettimeofday();
	philo->eat_cnt++;
	x_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(philo->left_fk);
	pthread_mutex_unlock(philo->right_fk);
}

void	sleeping_philo(t_philos *philo)
{
	do_write(philo, "sleep");
	x_usleep(philo->data->time_to_sleep);
}

void	thinking_philo(t_philos *philo)
{
	do_write(philo, "think");
}

void	action_philo(t_philos *philo)
{
	eating_philo(philo);
	sleeping_philo(philo);
	thinking_philo(philo);
}
