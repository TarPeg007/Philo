/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfellahi <sfellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 11:08:03 by sfellahi          #+#    #+#             */
/*   Updated: 2024/11/03 15:24:56 by sfellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_valid_argument(const char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == '+')
		i++;
	if (!str[i])
		return (false);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (false);
		i++;
	}
	return (true);
}

int	parse_arguments(int argc, char **argv, t_data *data)
{
	int	i;

	if (argc < 5 || argc > 6)
	{
		ft_putstr_fd("Error: Invalid number of arguments\n", 2);
		return (0);
	}
	i = 1;
	while (i < argc)
	{
		if (!is_valid_argument(argv[i]) || ft_is_overflow(argv[i]))
		{
			ft_putstr_fd("Error: Invalid argument or number overflow\n", 2);
			return (0);
		}
		i++;
	}
	data->number_of_philosophers = ft_atoll(argv[1]);
	data->time_to_die = ft_atoll(argv[2]);
	data->time_to_eat = ft_atoll(argv[3]);
	data->time_to_sleep = ft_atoll(argv[4]);
	if (argc == 6)
		data->number_of_times_each_philosopher_must_eat = ft_atoll(argv[5]);
	else
		data->number_of_times_each_philosopher_must_eat = -1;
	return (data->number_of_philosophers > 0 && data->time_to_die > 0
		&& data->time_to_eat > 0 && data->time_to_sleep > 0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (!parse_arguments(argc, argv, &data))
		return (1);
	if (!init_data(&data))
	{
		ft_putstr_fd("Error: Initialization failed\n", 2);
		return (1);
	}
	start_simulation(&data);
	cleanup(&data);
	return (0);
}
