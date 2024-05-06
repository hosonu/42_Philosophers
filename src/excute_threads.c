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

void	*count_ate(void	*arg)
{
	t_philos *philo;

	philo = (t_philos *)arg;
	pthread_mutex_lock(&philo->data->mutex_for_wrt);
	printf("death time: %d", philo->data->death);
	pthread_mutex_unlock(&philo->data->mutex_for_wrt);
	while(philo->data->death == 0)
	{
		pthread_mutex_lock(&philo->mutex);
		if (philo->data->fin >= philo->data->num_philo)
			philo->data->death = 1;
		pthread_mutex_unlock(&philo->mutex);
	}
	return ((void *)0);
}

void	*observe_philo(void	*arg)
{
	t_philos	*philo;

	philo = (t_philos *)arg;
	while (1)
	{
		pthread_mutex_lock(&philo->data->mutex);
        if (philo->data->death != 0)
		{
            pthread_mutex_unlock(&philo->data->mutex);
            break;
        }
        pthread_mutex_unlock(&philo->data->mutex);
		pthread_mutex_lock(&philo->mutex);
		if (x_gettimeofday() >= philo->time_of_death && philo->is_eating == 0)
		{
			pthread_mutex_lock(&philo->data->mutex);
			write_actions("died", philo);
			philo->data->death = 1;
			pthread_mutex_unlock(&philo->data->mutex);
		}
		pthread_mutex_unlock(&philo->mutex);
		pthread_mutex_lock(&philo->data->mutex);
		if (philo->eat_cnt == philo->data->num_must_eat)
		{
			philo->eat_cnt++;
			philo->data->fin++;
		}
		pthread_mutex_unlock(&philo->data->mutex);
	}
	return ((void *)0);
}

void	*routine(void *arg)
{
	t_philos *philo;

	philo = (t_philos *)arg;
	pthread_mutex_lock(&philo->mutex);
	philo->time_of_death = philo->data->time_to_die + x_gettimeofday();
	if(pthread_create(&philo->threads, NULL, &observe_philo, (void *)philo))
		return ((void *)1);
	pthread_mutex_unlock(&philo->mutex);
	while (philo->data->death == 0)
	{
		// pthread_mutex_lock(&philo->mutex);
		doing_something(philo);//eating & sleep
		// pthread_mutex_unlock(&philo->mutex);
	}
	// if(pthread_join(philo->threads, NULL) == 1)
	// 	return ((void *)1);
	return ((void *)0);
}

int	excute_threads(t_data_arg *data)
{
	int i;
	pthread_t tid;

	i = 0;
	data->start = x_gettimeofday();
	if(data->num_must_eat > 0)
	{
		if(pthread_create(&tid, NULL, &count_ate, &data->philos[0]))
			return (1);
	}
	while(i < data->num_philo)
	{
		if(pthread_create(&data->philos[i].threads, NULL, &routine, &data->philos[i]))
			return (1);
		x_usleep(1);
		i++;
	}
	i = 0;
	while(i < data->num_philo)
	{
		if (pthread_join(data->philos[i].threads, NULL))
			return (1);
		i++;
	}
	return (0);
}
