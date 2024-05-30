# include "../philosophers.h"

int	is_dead(t_philos *philo)
{

}

void	eating_philo(t_philos *philo)
{
	pthread_mutex_lock(philo->left_fk);

	pthread_mutex_lock(philo->mutex);
	do_write(philo, "fork");
	do_write(philo, "fork");
	do_write(philo, "eat");
	pthread_mutex_unlock(philo->mutex);

	pthread_mutex_unlock(philo->left_fk);
}

void	sleeping_philo(t_philos *philo)
{
	pthread_mutex_lock(philo->mutex);
	do_write(philo, "sleep");
	pthread_mutex_unlock(philo->mutex);
}

void	thinking_philo(t_philos *philo)
{
	pthread_mutex_lock(philo->mutex);
	do_write(philo, "think");
	pthread_mutex_unlock(philo->mutex);
}

void	action_philo(t_philos *philo)
{
	eating_philo(philo);
	sleeping_philo(philo);
	thinking_philo(philo);
}
