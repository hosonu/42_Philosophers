/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosonu <hoyuki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 01:42:08 by hosonu            #+#    #+#             */
/*   Updated: 2024/05/05 01:42:12 by hosonu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	init_data_args(t_data_arg *data, int argc, char **argv)
{
	data->num_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->num_must_eat = ft_atoi(argv[5]);
	else
		data->num_must_eat = -1;
	if(data->num_philo <= 0 || data->num_philo > 200 || data->time_to_die < 0
		|| data->time_to_eat < 0 || data->time_to_sleep < 0)
		return (1);
	data->death = 0;
	data->fin = 0;
	pthread_mutex_init(&data->mutex, NULL);
	pthread_mutex_init(&data->mutex_for_wrt, NULL);
	return (0);
}

int allocate_datas(t_data_arg *data)
{
	data->thread = malloc(sizeof(pthread_t) * data->num_philo);
	if (data->thread == NULL)
		return (1);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philo);
	if(data->forks == NULL)
		return (1);
	data->philos = malloc(sizeof(t_philos) * data->num_philo);
	if (data->philos == NULL)
		return (1);
	return (0);

}

void	init_forks(t_data_arg *data)
{
	int i;

	i = 0;
	while(i < data->num_philo)
	{
		data->philos[i].no = i + 1;
		data->philos[i].left_fork_id = i;
        data->philos[i].right_fork_id = (i + 1) % data->num_philo;
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	data->philos[0].left_fk = &data->forks[0];
	data->philos[0].right_fk = &data->forks[data->num_philo - 1];
	i = 1;
	while(i < data->num_philo)
	{
		data->philos[i].left_fk = &data->forks[i];
		data->philos[i].right_fk = &data->forks[i - 1];
		i++;
	}
}

int init_threads(t_data_arg *data)
{
	int i;

	if(allocate_datas(data) == 1)
		return (1);
	init_forks(data);
	i = 0;
	while (i < data->num_philo)
	{
		data->philos[i].data = data;
		data->philos[i].time_of_death = data->time_to_die;
		data->philos[i].eat_cnt = 0;
		data->philos[i].is_eating = 0;
		data->philos[i].status = 0;
		pthread_mutex_init(&data->philos[i].mutex, NULL);
		i++;
	}
	return (0);
}

int	init_data(t_data_arg *data, int argc, char **argv)
{
	if (init_data_args(data, argc, argv) == 1)
		return (1);
	if (init_threads(data) == 1)
		return (1);
	return (0);
}
