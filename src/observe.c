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

# include "../philosophers.h"

void	dissolution_announcement(t_philos *philo)
{
	while(philo->dissolution == 0)
	{
		pthread_mutex_lock(&philo->dissolute_mtx);
		philo->dissolution = 1;
		pthread_mutex_unlock(philo->left_fk);
		pthread_mutex_unlock(philo->right_fk);
		pthread_mutex_unlock(&philo->dissolute_mtx);
		philo = philo->next;
	}
}

void	*observe_philo(void *data)
{
	t_philos *philo;

	philo = (t_philos *)data;
	while(1)
	{
		if (x_gettimeofday() - philo->time_after_ate > philo->data->time_to_die)
		{
			pthread_mutex_lock(&philo->death_mutex);
			philo->is_dead = 1;
			do_write(philo, "death");
			pthread_mutex_unlock(&philo->death_mutex);
			dissolution_announcement(philo);
			break;
		}
		if (philo->eat_cnt == philo->data->num_must_eat)
		{
			dissolution_announcement(philo);
			break;
		}
		philo = philo->next;
	}
	return (NULL);
}
