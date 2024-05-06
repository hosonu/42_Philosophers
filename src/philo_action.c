/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosonu <hoyuki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 23:48:13 by hosonu            #+#    #+#             */
/*   Updated: 2024/05/05 23:48:24 by hosonu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	write_actions(char *str, t_philos *philo)
{
	unsigned int	time;

	pthread_mutex_lock(&philo->data->mutex);
	time = x_gettimeofday() - philo->data->start;
	if(ft_strcmp("died", str) == 0 && philo->data->death == 0)
	{
		printf("%d %d death\n", time, philo->no);
		philo->data->death = 1;
	}
	if(philo->data->death == 0)
		printf("%d %d %s\n", time, philo->no, str);
	pthread_mutex_unlock(&philo->data->mutex);
}

// void	doing_something(t_philos *philo)
// {
// 	pthread_mutex_lock(&philo->mutex);
// 	pthread_mutex_lock(philo->right_fk);
// 	write_actions("take right", philo);
// 	pthread_mutex_lock(philo->left_fk);
// 	write_actions("take left", philo);
// 	philo->is_eating = 1;
// 	philo->time_of_death = x_gettimeofday() + philo->data->time_to_die;
// 	write_actions("eating", philo);
// 	philo->eat_cnt++;
// 	x_usleep(philo->data->time_to_eat);
// 	philo->is_eating = 0;
// 	pthread_mutex_unlock(philo->right_fk);
// 	pthread_mutex_unlock(philo->left_fk);
// 	write_actions("sleeping", philo);
// 	x_usleep(philo->data->time_to_sleep);
// 	write_actions("thinking", philo);
// 	pthread_mutex_unlock(&philo->mutex);
// }
void doing_something(t_philos *philo)
{
    pthread_mutex_t *first_fork;
    pthread_mutex_t *second_fork;

    // フォークのIDに基づいて取得順序を決定
    if (philo->left_fork_id < philo->right_fork_id) {
        first_fork = philo->left_fk;
        second_fork = philo->right_fk;
    } else {
        first_fork = philo->right_fk;
        second_fork = philo->left_fk;
    }

    // 一貫した順序でフォークを取得
    pthread_mutex_lock(first_fork);
    write_actions("take first fork", philo);
    pthread_mutex_lock(second_fork);
    write_actions("take second fork", philo);

    // 食事の処理
    pthread_mutex_lock(&philo->mutex);
    philo->is_eating = 1;
    philo->time_of_death = x_gettimeofday() + philo->data->time_to_die;
    write_actions("eating", philo);
    philo->eat_cnt++;
    x_usleep(philo->data->time_to_eat);
    philo->is_eating = 0;
    pthread_mutex_unlock(&philo->mutex);

    // フォークを解放
    pthread_mutex_unlock(second_fork);
    pthread_mutex_unlock(first_fork);

    // pthread_mutex_lock(&philo->mutex);
    write_actions("sleeping", philo);
    x_usleep(philo->data->time_to_sleep);
	// write_actions("thinking", philo);
	// pthread_mutex_unlock(&philo->mutex);
}

