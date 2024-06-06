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
	while (philo->is_dead == 0)
	{
		pthread_mutex_lock(&philo->death_mutex);
		philo->is_dead = 1;
		pthread_mutex_unlock(&philo->death_mutex);
		pthread_mutex_unlock(philo->left_fk);
		pthread_mutex_unlock(philo->right_fk);
		philo = philo->next;
	}
	if (philo->data->num_philo == 1)
		pthread_mutex_unlock(philo->left_fk);
	return (NULL);
}

int	check_all_philo_eaten(t_philos *philo)
{
	int			cnt;
	int			i;

	i = 0;
	cnt = 0;
	while (i < philo->data->num_philo)
	{
		pthread_mutex_lock(&philo->eat_mutex);
		if (philo->eat_cnt >= philo->data->num_must_eat)
		{
			pthread_mutex_unlock(&philo->eat_mutex);
			cnt++;
		}
		pthread_mutex_unlock(&philo->eat_mutex);
		pthread_mutex_lock(&philo->eat_mutex);
		if (cnt == philo->data->num_philo)
		{
			pthread_mutex_unlock(&philo->eat_mutex);
			return (0);
		}
		pthread_mutex_unlock(&philo->eat_mutex);
		philo = philo->next;
		i++;
	}
	return (1);
}

void	declare_death(t_philos *philo)
{
	pthread_mutex_lock(&philo->death_mutex);
	philo->is_dead = 1;
	pthread_mutex_unlock(&philo->death_mutex);
	do_write(philo, "death");
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
			declare_death(philo);
			return (dissolution_announcement(philo->next));
		}
		pthread_mutex_unlock(&philo->eat_mutex);
		pthread_mutex_lock(&philo->eat_mutex);
		if (philo->data->num_must_eat != -1
			&& philo->eat_cnt >= philo->data->num_must_eat)
		{
			pthread_mutex_unlock(&philo->eat_mutex);
			if (check_all_philo_eaten(philo) == 0)
				return (dissolution_announcement(philo));
		}
		pthread_mutex_unlock(&philo->eat_mutex);
		philo = philo->next;
	}
	return (NULL);
}
