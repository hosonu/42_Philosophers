/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosonu <hoyuki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 13:47:25 by hosonu            #+#    #+#             */
/*   Updated: 2024/05/31 13:47:32 by hosonu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

static void	taking_fork(t_philos *philo)
{
	if (philo->no % 2 == 0)
		pthread_mutex_lock(philo->left_fk);
	else
		pthread_mutex_lock(philo->right_fk);
	do_write(philo, "fork");
	if (philo->no % 2 == 0)
		pthread_mutex_lock(philo->right_fk);
	else
		pthread_mutex_lock(philo->left_fk);
	do_write(philo, "fork");
}

static void	eating_philo(t_philos *philo)
{
	taking_fork(philo);
	pthread_mutex_lock(&philo->eat_mutex);
	philo->time_after_ate = x_gettimeofday();
	philo->eat_cnt++;
	philo->is_eating = 1;
	pthread_mutex_unlock(&philo->eat_mutex);
	do_write(philo, "eat");
	pthread_mutex_lock(&philo->death_mutex);
	if (philo->is_dead != 1)
	{
		pthread_mutex_unlock(&philo->death_mutex);
		x_usleep(philo->data->time_to_eat);
	}
	else
		pthread_mutex_unlock(&philo->death_mutex);
	// 	pthread_mutex_unlock(&philo->dissolute_mtx);
	pthread_mutex_unlock(philo->left_fk);
	pthread_mutex_unlock(philo->right_fk);
}

static void	sleeping_philo(t_philos *philo)
{
	pthread_mutex_lock(&philo->eat_mutex);
	philo->is_eating = 0;
	pthread_mutex_unlock(&philo->eat_mutex);
	do_write(philo, "sleep");
	if (philo->dissolution != 1)
		x_usleep(philo->data->time_to_sleep);
}

static void	thinking_philo(t_philos *philo)
{
	do_write(philo, "think");
}

void	action_philo(t_philos *philo)
{
	eating_philo(philo);
	sleeping_philo(philo);
	thinking_philo(philo);
}
