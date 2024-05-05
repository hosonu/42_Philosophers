/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosonu <hoyuki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 01:41:39 by hosonu            #+#    #+#             */
/*   Updated: 2024/05/05 01:41:41 by hosonu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	detect_argv(char *argv[])
{
	int	i;
	int	j;

	i = 1;
	while (argv[i] != NULL)
	{
		j = 0;
		while (argv[i][j] != '\0')
		{
			if (argv[i][j] == ' ')
			{
				j++;
				continue;
			}
			if ((argv[i][j] < '0' || argv[i][j] > '9'))
				return (1);
		}
		j++;
	}
	i++;
	return (0);
}

void	destroy_threads(t_data_arg *data)
{
	int i;

	i = 0;
	while(i < data->num_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philos[i].mutex);
	}
	pthread_mutex_destroy(&data->mutex_for_wrt);
	pthread_mutex_destroy(&data->mutex);
}

int main(int argc, char *argv[])
{
	t_data_arg data;

	if(argc < 5 || argc > 6)
	{
		printf("argc");
		return (1);
	}
	if (detect_argv(argv) == 1)
	{
		printf("argv");
		return (1);
	}
	if(init_data(&data, argc, argv) == 1)
	{
		printf("init");
		return (1);
	}
	excute_threads(&data);
	destroy_threads(&data);
	return (0);
}
