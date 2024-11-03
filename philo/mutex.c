/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfellahi <sfellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 12:06:16 by sfellahi          #+#    #+#             */
/*   Updated: 2024/11/03 14:54:12 by sfellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutexes(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->number_of_philosophers);
	if (!data->forks)
		return (0);
	if (pthread_mutex_init(&data->stop_mutex, NULL) != 0)
	{
		free(data->forks);
		return (0);
	}
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&data->stop_mutex);
		free(data->forks);
		return (0);
	}
	i = 0;
	while (i < data->number_of_philosophers)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&data->forks[i]);
			pthread_mutex_destroy(&data->stop_mutex);
			pthread_mutex_destroy(&data->print_mutex);
			free(data->forks);
			return (0);
		}
		i++;
	}
	return (1);
}

int	init_philosophers(t_data *data)
{
	int	i;

	data->philosophers = malloc(sizeof(t_philosopher) * data->number_of_philosophers);
	if (!data->philosophers)
		return (0);
	i = 0;
	while (i < data->number_of_philosophers)
	{
		data->philosophers[i].id = i + 1;
		data->philosophers[i].left_fork = &data->forks[i];
		data->philosophers[i].right_fork = &data->forks[(i + 1) % data->number_of_philosophers];
		data->philosophers[i].data = data;
		data->philosophers[i].last_meal_time = get_current_time();
		data->philosophers[i].meals_eaten = 0;
		if (pthread_mutex_init(&data->philosophers[i].meal_mutex, NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&data->philosophers[i].meal_mutex);
			return (0);
		}
		i++;
	}
	return (1);
}

void	cleanup(t_data *data)
{
	int	i;

	if (data->forks)
	{
		i = 0;
		while (i < data->number_of_philosophers)
		{
			pthread_mutex_destroy(&data->forks[i]);
			pthread_mutex_destroy(&data->philosophers[i].meal_mutex);
			i++;
		}
		free(data->forks);
	}
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->stop_mutex);
	if (data->philosophers)
		free(data->philosophers);
}

int	init_data(t_data *data)
{
	data->simulation_stop = false;
	if (!init_mutexes(data))
	{
		ft_putstr_fd("Error: Failed to initialize mutexes\n", 2);
		return (0);
	}
	if (!init_philosophers(data))
	{
		ft_putstr_fd("Error: Failed to initialize philosophers\n", 2);
		cleanup(data);
		return (0);
	}
	return (1);
}
