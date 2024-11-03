/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfellahi <sfellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 11:14:25 by sfellahi          #+#    #+#             */
/*   Updated: 2024/11/03 14:51:14 by sfellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	smart_sleep(long long duration, t_data *data)
{
	long long	start;
	long long	elapsed;

	start = get_current_time();
	while ((elapsed = get_current_time() - start) < duration)
	{
		pthread_mutex_lock(&data->stop_mutex);
		if (data->simulation_stop)
		{
			pthread_mutex_unlock(&data->stop_mutex);
			return ;
		}
		pthread_mutex_unlock(&data->stop_mutex);
		usleep(500);
	}
}

bool	ft_is_overflow(const char *str)
{
	long long	num;
	int			i;

	num = 0;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (num > INT_MAX / 10 || (num == INT_MAX / 10 && (str[i] - '0') > INT_MAX % 10))
			return (true);
		num = num * 10 + (str[i] - '0');
		i++;
	}
	return (false);
}

long long	ft_atoll(const char *str)
{
	long long	res;
	int			i;

	res = 0;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res);
}

long long	get_current_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
	{
		ft_putstr_fd("Error: gettimeofday failed\n", 2);
		return (-1);
	}
	return ((long long)tv.tv_sec * 1000 + (long long)tv.tv_usec / 1000);
}

void	ft_putstr_fd(char *str, int fd)
{
	if (fd < 0 || !str)
		return ;
	while (*str)
		write(fd, str++, 1);
}
