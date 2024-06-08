/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosonu <hoyuki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 01:42:52 by hosonu            #+#    #+#             */
/*   Updated: 2024/05/05 01:42:54 by hosonu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	x_gettimeofday(void)
{
	struct timeval	tv;
	long			time;

	if (gettimeofday(&tv, NULL) == -1)
		return (-1);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time);
}

void	x_usleep(long time)
{
	long	start;
	long	elapsed;

	start = x_gettimeofday();
	while (1)
	{
		elapsed = x_gettimeofday() - start;
		if (elapsed >= time)
			return ;
		usleep(100);
	}
}

static long	ft_strtol(const char *str, int sign)
{
	long	result;
	long	tmp;

	result = 0;
	while (*str && *str >= '0' && *str <= '9')
	{
		tmp = result;
		result = result * 10 + *str - '0';
		if (result < tmp)
		{
			if (sign == -1)
				return (LONG_MIN);
			else
				return (LONG_MAX);
		}
		str++;
	}
	return (result * sign);
}

long	ft_atol(const char *str)
{
	long	result;
	int		sign;
	int		sign_fg;

	sign_fg = 0;
	result = 0;
	sign = 1;
	while (*str && (*str == ' ' || (*str >= 9 && *str <= 13)))
		str++;
	while (*str && (*str == '+' || *str == '-'))
	{
		if (*str == '-')
			sign *= -1;
		if (sign_fg == 1)
			return (result);
		sign_fg = 1;
		str++;
	}
	return ((ft_strtol(str, sign)));
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
	{
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
