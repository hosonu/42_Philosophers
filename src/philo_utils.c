# include "../philosophers.h"

void	do_write(t_philos *philo, char *state)
{
        pthread_mutex_lock(&philo->wrt_mtx);
        if(ft_strcmp(state, "fork"))
                printf("%ld %d %s\n",
                get_elapsedtime(philo->start), philo->no, "has taken a fork");
	else if(ft_strcmp(state, "eat"))
                printf("%ld %d %s\n",
                get_elapsedtime(philo->start), philo->no, "is eating");
        else if(ft_strcmp(state, "think"))
                printf("%ld %d %s\n",
                get_elapsedtime(philo->start), philo->no, "is thinking");
        else if(ft_strcmp(state, "sleep"))
                printf("%ld %d %s\n",
                get_elapsedtime(philo->start), philo->no, "is sleeping");
        else if(ft_strcmp(state, "death"))
                printf("%ld %d %s\n",
                get_elapsedtime(philo->start), philo->no, "is dead");
        pthread_mutex_unlock(&philo->wrt_mtx);
        
}

long    get_elapsedtime(long start_time)
{
        long current_time;

        current_time = x_gettimeofday();
        return (current_time - start_time);
}