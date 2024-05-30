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

#include "../philosophers.h"

int	x_gettimeofday(void)
{
	struct timeval tv;

	if(gettimeofday(&tv, NULL) == -1)
		return(-1);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	x_usleep(useconds_t time)
{
	unsigned int	start;

	start = (unsigned int)x_gettimeofday();
	while ((x_gettimeofday() - start) < time)
		usleep(time / 10);
	return (0);
}

static long     ft_strtol(const char *str, int sign)
{
        long    result;
        long    tmp;

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

long     ft_atoi(const char *str)
{
        long    result;
        int             sign;
        int             sign_fg;

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
	while (*s1 != '\0' && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*(char *)s1 - *(char *)s2);
}
