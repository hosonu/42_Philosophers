/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosonu <hoyuki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 13:47:50 by hosonu            #+#    #+#             */
/*   Updated: 2024/05/31 13:47:52 by hosonu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	*dissolution_announcement(t_philos *philo)
{
	t_philos	*start;

	start = philo;
	while (1)
	{
		pthread_mutex_lock(&philo->dissolute_mtx);
		if (philo->dissolution == 0)
		{
			philo->dissolution = 1;
			if (pthread_mutex_trylock(philo->left_fk) == 0
				|| philo->data->num_philo == 1)
				pthread_mutex_unlock(philo->left_fk);
			if (pthread_mutex_trylock(philo->right_fk) == 0)
				pthread_mutex_unlock(philo->right_fk);
		}
		pthread_mutex_unlock(&philo->dissolute_mtx);
		philo = philo->next;
		if (philo == start)
			break ;
	}
	return (NULL);
}

void	*observe_philo(void *data)
{
	t_philos	*philo;

	philo = (t_philos *)data;
	while (1)
	{
		pthread_mutex_lock(&philo->eat_mutex);
		if (x_gettimeofday() - philo->time_after_ate > philo->data->time_to_die)
		{
			pthread_mutex_unlock(&philo->eat_mutex);
			pthread_mutex_lock(&philo->death_mutex);
			philo->is_dead = 1;
			pthread_mutex_unlock(&philo->death_mutex);
			do_write(philo, "death");
			return (dissolution_announcement(philo));
		}
		if (philo->eat_cnt == philo->data->num_must_eat)
		{
			pthread_mutex_unlock(&philo->eat_mutex);
			return (dissolution_announcement(philo));
		}
		pthread_mutex_unlock(&philo->eat_mutex);
		philo = philo->next;
	}
	return (NULL);
}
