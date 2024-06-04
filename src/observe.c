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

// static void	*dissolution_announcement(t_philos *philo)
// {
// 	t_philos	*start;

// 	start = philo;
// 	while (1)
// 	{
// 		pthread_mutex_lock(&philo->death_mutex);
// 		if (philo->is_dead == 0)
// 		{
// 			philo->is_dead = 1;
// 			pthread_mutex_unlock(philo->left_fk);
// 			pthread_mutex_unlock(philo->right_fk);
// 		}
// 		if (philo->data->num_philo == 1)
// 			pthread_mutex_unlock(philo->left_fk);
// 		pthread_mutex_unlock(&philo->death_mutex);
// 		philo = philo->next;
// 		if (philo == start)
// 			break ;
// 	}
// 	return (NULL);
// }

void	*dissolution_announcement(t_philos *philo)
{
	t_philos	*start;

	start = philo;
	while (philo->is_dead == 0)
	{
		pthread_mutex_lock(&philo->death_mutex);
		philo->is_dead = 1;
		pthread_mutex_unlock(&philo->death_mutex);
		pthread_mutex_unlock(philo->left_fk);
		pthread_mutex_unlock(philo->right_fk);
		philo = philo->next;
	}
	if (philo->data->num_philo)
		pthread_mutex_unlock(philo->left_fk);
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
			return (dissolution_announcement(philo->next));
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
