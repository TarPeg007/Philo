/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfellahi <sfellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 13:37:30 by sfellahi          #+#    #+#             */
/*   Updated: 2024/11/02 12:07:37 by sfellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void start_philosopher(t_data *data)
{
    int i;
    
    data->start_time = get_current_time();
    i = 0;
    while (i < data->number_of_philosophers)
    {
        data->philosophers[i].last_meal_time = data->start_time;
        if (pthread_create(&data->philosophers[i].thread, NULL,
                        philosopher_routine,&data->philosophers[i] ) != 0)
        {
            set_simulation_stop(data);
            ft_putstr_fd("Error: Failed to create thread\n", 2);
            return;
        }
        i++;
    }
}

void start_simulation(t_data *data)
{
	pthread_t monitor;
	int	i;

	start_philosopher(data);
	if (pthread_create(&monitor, NULL, (void *(*)(void *))check_death, data) != 0)
	{
		set_simulation_stop(data);
		ft_putstr_fd("Error: Failed to create monitor thread\n",2);
		return ;
	}
	pthread_join(monitor, NULL);
	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_join(data->philosophers[i].thread, NULL);
		i++;
	}
}

void *philosopher_routine(void *arg)
{
    t_philosopher *philo = (t_philosopher *)arg;
    
    if (philo->data->number_of_philosophers == 1)
    {
        print_status(philo, "has taken a fork");
        smart_sleep(philo->data->time_to_die, philo->data);
        return NULL;
    }
    if (philo->id % 2 == 0)
        smart_sleep(1, philo->data);
    while (!is_simulation_stopped(philo->data))
    {
        eat(philo, philo->data);
        if (is_simulation_stopped(philo->data))
            break ;
        print_status(philo, "is sleeping");
        smart_sleep(philo->data->time_to_sleep, philo->data);
        if (is_simulation_stopped(philo->data))
            break ;
        print_status(philo, "is thinking");
        if (philo->data->number_of_philosophers > 50)
            smart_sleep(1, philo->data);
    }
    return NULL;
}

void check_death(t_data *data)
{
    int i;
    long long current_time;
    long long last_meal;
    bool all_ate_enough;

    while (!is_simulation_stopped(data))
    {
        i = 0;
        all_ate_enough = true;
        while (i < data->number_of_philosophers && !is_simulation_stopped(data))
        {
            current_time = get_current_time();
            pthread_mutex_lock(&data->philosophers[i].meal_mutex);
            last_meal = data->philosophers[i].last_meal_time;
            if (data->number_of_times_each_philosopher_must_eat != -1 && 
                data->philosophers[i].meals_eaten < data->number_of_times_each_philosopher_must_eat)
                all_ate_enough = false;
			pthread_mutex_unlock(&data->philosophers[i].meal_mutex);
			if (current_time - last_meal > data->time_to_die)
			{
				set_simulation_stop(data);
				printf("%lld %d %s\n", current_time -  data->start_time , data->philosophers[i].id, "died");
                return;
            }
            i++;
        }
        if (data->number_of_times_each_philosopher_must_eat != -1 && all_ate_enough)
        {
            set_simulation_stop(data);
            return;
        }
        usleep(1000);
    }
}
