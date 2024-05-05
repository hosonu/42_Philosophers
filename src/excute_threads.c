/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excute_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosonu <hoyuki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 01:41:51 by hosonu            #+#    #+#             */
/*   Updated: 2024/05/05 01:41:56 by hosonu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	*observe_philo(void	*arg)
{
	t_philos	*philo;

	philo = (t_philos *)arg;
	while (philo->data->death == 0)
	{
		pthread_mutex_lock(&philo->mutex);
		if (x_gettimeofday() >= philo->time_of_death && philo->is_eating == 0)
		{
			write_actions("died", philo);
		}
		if (philo->eat_cnt == philo->data->num_must_eat)
		{
			pthread_mutex_lock(&philo->data->mutex);
			philo->data->fin++;
			philo->eat_cnt++;
			pthread_mutex_unlock(&philo->data->mutex);
		}
		pthread_mutex_unlock(&philo->mutex);
	}
	return ((void *)0);
}

void	*routine(void *arg)
{
	t_philos *philo;

	philo = (t_philos *)arg;
	philo->time_of_death = philo->data->time_to_die + x_gettimeofday();
	if(pthread_create(&philo->threads, NULL, &observe_philo, (void *)philo))
		return ((void *)1);
	while (philo->data->death == 0)
	{
		doing_something(philo);//eating & sleep
		write_actions("thinking", philo);
	}
	if(pthread_join(philo->threads, NULL) == 1)
		return ((void *)1);
	return ((void *)0);
}

int	excute_threads(t_data_arg *data)
{
	int i;

	data->start = x_gettimeofday();
	i = 0;
	while(i < data->num_philo)
	{
		if(pthread_create(&data->thread[i], NULL, &routine, &data->philos[i]))
			return (1);
		x_usleep(1);
		i++;
	}
	i = 0;
	while(i < data->num_philo)
	{
		if (pthread_join(data->thread[i], NULL))
			return (1);
		i++;
	}
	return (0);
}
