/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-05-30 04:09:03 by user              #+#    #+#             */
/*   Updated: 2024/05/30 13:09:33 by hosonu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	do_write(t_philos *philo, char *state)
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
			"is dead");
	pthread_mutex_unlock(philo->wrt_mtx);
}

long	get_elapsedtime(long start_time)
{
	long	current_time;

	current_time = x_gettimeofday();
	return (current_time - start_time);
}
