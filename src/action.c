# include "../philosophers.h"

void	do_write(t_philos *philo)
{
	pthread_mutex_lock(philo->wrt_mtx);
	
}

int	is_dead(t_philos *philo)
{

}

void	eating_philo(t_philos *philo)
{
	pthread_mutex_lock(philo->left_fk);
	do_write(philo);

}

void	sleeping_philo(t_philos *philo)
{

}

void	thinking_philo(t_philos *philo)
{

}

void	action_philo(t_philos *philo)
{
	eating_philo(philo);
	sleeping_philo(philo);
	thinking_philo(philo);
}
