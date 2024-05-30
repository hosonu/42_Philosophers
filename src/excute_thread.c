
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excute_thread.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-05-25 04:33:46 by user              #+#    #+#             */
/*   Updated: 2024-05-25 04:33:46 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../philosophers.h"

void	*philo_routine(void	*data)
{
	t_philos *philo;

	philo = (t_philos *)data;
	while(is_dead(philo) != false)
		action_philo(philo);
	return (NULL);
}

int	excute_thread(t_philos *philo)
{
	int i;
	int ret;


	i = 0;
	while(i < philo->data->num_philo)
	{
		ret = pthread_create(&(philo->thread), NULL, philo_routine, (void *)philo);
		philo = philo->next;
		i++;
		usleep(10);
	}
	return (ret);
}
