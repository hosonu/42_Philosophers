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

# include "../philosophers.h"

static int init_mutex(t_philos *philo)
{
	pthread_mutex_init(&philo->mutex, NULL);
	philo->left_fk = malloc(sizeof(pthread_mutex_t));
	if (philo->left_fk == NULL)
		return (1);
	pthread_mutex_init(philo->left_fk, NULL);
	philo->wrt_mtx = malloc(sizeof(pthread_mutex_t));
	if (philo->wrt_mtx == NULL)
		return (1);
	pthread_mutex_init(philo->wrt_mtx, NULL);
	return (0);
}

void	set_data(t_data_arg *data, char **argv)
{
	data->num_philo = ft_atoi(argv[1]);
	data->time_to_die =  ft_atoi(argv[2]);
	data->time_to_eat =  ft_atoi(argv[3]);
	data->time_to_sleep =  ft_atoi(argv[4]);
	if (argv[5] != NULL)
		data->num_must_eat =  ft_atoi(argv[5]);
	else
		data->num_must_eat = -1;

}

static int	add_data(t_philos *philo, t_data_arg *datas, int i)
{
	philo->data = datas;
	philo->is_eating = 0;
	philo->no = i;
	philo->is_dead = 0;
	philo->eat_cnt = 0;
	philo->start = x_gettimeofday();
	if(init_mutex(philo) == 1)
		return (false);
	return (0);
}

static void	make_list(t_philos *philo, t_philos *new)
{
	philo->next = new;
	new->right_fk = philo->left_fk;
	new->next = NULL;
}

int	init_data(t_data_arg *data, char *argv[])
{
	t_philos	*philo;
	t_philos	*head;
	int			i;

	i = 1;
	set_data(data, argv);
	head = malloc(sizeof(t_philos));
	if (add_data(head, data, i) == 1)
		return (false);
	data->philo = head;
	while (ft_atoi(argv[1]) >= i)
	{
		philo = malloc(sizeof(t_philos) * 1);
		if (philo == NULL)
		 	return (false);
		if (add_data(philo, data, i + 1) == 1)
			return (false);
		make_list(head, philo);
		head = philo;
		i++;
	}
	philo->next = data->philo;
	data->philo->right_fk = philo->left_fk;
	return (0);
}
