/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoyuki <hoyuki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 04:09:03 by user              #+#    #+#             */
/*   Updated: 2024/06/06 15:47:45 by hoyuki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	mutex_init_error(pthread_mutex_t *mutex)
{
	int	ret;

	ret = pthread_mutex_init(mutex, NULL);
	if (ret == ENOMEM)
		printf("Insufficient memory to initialize mutex\n");
	else if (ret == EAGAIN)
	{
		printf("Failed to initialize mutex as the required");
		printf(" resource is temporarily unavaiable\n");
	}
	return (ret);
}

static void	do_write_utils(t_philos *philo, char *state)
{
	pthread_mutex_lock(philo->wrt_mtx);
	if (ft_strcmp(state, "fork") == 0)
		printf("%ld %d %s\n", get_elapsedtime(philo->start), philo->no,
			"has taken a fork");
	else if (ft_strcmp(state, "eat") == 0)
		printf("%ld %d %s\n", get_elapsedtime(philo->start), philo->no,
			"is eating");
	else if (ft_strcmp(state, "think") == 0)
		printf("%ld %d %s\n", get_elapsedtime(philo->start), philo->no,
			"is thinking");
	else if (ft_strcmp(state, "sleep") == 0)
		printf("%ld %d %s\n", get_elapsedtime(philo->start), philo->no,
			"is sleeping");
	else if (ft_strcmp(state, "death") == 0)
		printf("%ld %d %s\n", get_elapsedtime(philo->start), philo->no,
			"diad");
	pthread_mutex_unlock(philo->wrt_mtx);
}

void	do_write(t_philos *philo, char *state)
{
	pthread_mutex_lock(&philo->death_mutex);
	if (philo->is_dead == 0)
	{
		pthread_mutex_unlock(&philo->death_mutex);
		do_write_utils(philo, state);
	}
	else
	{
		pthread_mutex_unlock(&philo->death_mutex);
		pthread_mutex_lock(philo->wrt_mtx);
		if (ft_strcmp(state, "death") == 0)
			printf("%ld %d %s\n", get_elapsedtime(philo->start), philo->no,
				"died");
		pthread_mutex_unlock(philo->wrt_mtx);
	}
}

long	get_elapsedtime(long start_time)
{
	long	current_time;

	current_time = x_gettimeofday();
	return (current_time - start_time);
}
