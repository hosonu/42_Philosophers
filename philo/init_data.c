/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-05-23 14:03:37 by user              #+#    #+#             */
/*   Updated: 2024-05-23 14:03:37 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	init_mutex(t_philos *philo)
{
	if (mutex_init_error(&philo->eat_mutex) != 0
		|| mutex_init_error(&philo->death_mutex) != 0)
		return (1);
	philo->left_fk = malloc(sizeof(pthread_mutex_t));
	if (philo->left_fk == NULL)
		return (1);
	if (mutex_init_error(philo->left_fk) != 0)
		return (1);
	philo->wrt_mtx = malloc(sizeof(pthread_mutex_t));
	if (philo->wrt_mtx == NULL)
		return (1);
	if (mutex_init_error(philo->wrt_mtx) != 0)
		return (1);
	return (0);
}

void	set_data(t_data_arg *data, char **argv)
{
	data->num_philo = ft_atol(argv[1]);
	data->time_to_die = ft_atol(argv[2]);
	data->time_to_eat = ft_atol(argv[3]);
	data->time_to_sleep = ft_atol(argv[4]);
	if (argv[5] != NULL)
		data->num_must_eat = ft_atol(argv[5]);
	else
		data->num_must_eat = -1;
}

static int	add_data(t_philos *philo, t_data_arg *datas, int i)
{
	philo->data = datas;
	philo->no = i;
	philo->is_dead = 0;
	philo->eat_cnt = 0;
	philo->time_after_ate = x_gettimeofday();
	philo->start = x_gettimeofday();
	if (i == 1)
	{
		datas->philo = philo;
		datas->philo->next = datas->philo;
	}
	if (init_mutex(philo) == 1)
		return (1);
	if (i == 1)
		datas->philo->right_fk = datas->philo->left_fk;
	return (0);
}

static void	make_list(t_philos *philo, t_philos *new)
{
	philo->next = new;
	new->right_fk = philo->left_fk;
	new->next = NULL;
}

int	init_data(t_data_arg *data, char *argv[], int *index)
{
	t_philos	*philo;
	t_philos	*head;

	set_data(data, argv);
	head = malloc(sizeof(t_philos));
	if (head == NULL || add_data(head, data, *index) == 1)
		return (1);
	while (ft_atol(argv[1]) > *index)
	{
		philo = malloc(sizeof(t_philos) * 1);
		if (philo == NULL || add_data(philo, data, *index + 1) == 1)
			return (1);
		make_list(head, philo);
		head = philo;
		(*index)++;
	}
	if (*index > 1)
	{
		philo->next = data->philo;
		data->philo->right_fk = philo->left_fk;
	}
	return (0);
}
