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
			j++;
		}
		i++;
	}
	return (0);
}

void destroy_philo(t_data_arg *data)
{
	int i;
	t_philos *tmp;

	i = 0;
	while(data->num_philo > i)
	{
		pthread_mutex_destroy(data->philo->left_fk);
		pthread_mutex_destroy(data->philo->wrt_mtx);
		pthread_mutex_destroy(&data->philo->death_mutex);
		pthread_mutex_destroy(&data->philo->eat_mutex);
		tmp = data->philo;
		data->philo = data->philo->next;
		free(tmp);
		i++;
	}
}

void	join_thread(t_data_arg *data)
{
	int i;
	t_philos *current_philo;

	i = 0;
	current_philo = data->philo;
	while (data->num_philo > i)
	{
		pthread_join(current_philo->thread, NULL);
		current_philo = current_philo->next;
		i++;
	}
}

int main(int argc, char *argv[])
{
	t_data_arg data;
	pthread_t	observe_th;

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
	if(init_data(&data, argv) == 1)
	{
		printf("init");
		return (1);
	}
	pthread_create(&observe_th, NULL, observe_philo, (void *)data.philo);
	if(excute_thread(data.philo) != 0)
		return (1);
	join_thread(&data);
	pthread_join(observe_th, NULL);
	destroy_philo(&data);
	return (0);
}
