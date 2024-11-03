/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfellahi <sfellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 13:46:12 by sfellahi          #+#    #+#             */
/*   Updated: 2024/10/31 17:57:36 by sfellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void set_simulation_stop(t_data *data)
{
    pthread_mutex_lock(&data->stop_mutex);
    data->simulation_stop = true;
    pthread_mutex_unlock(&data->stop_mutex);
}

bool is_simulation_stopped(t_data *data)
{
   // bool stopped;
    
    pthread_mutex_lock(&data->stop_mutex);
    if (data->simulation_stop == true)
        {
            pthread_mutex_unlock(&data->stop_mutex);
            return (1);
        }
    pthread_mutex_unlock(&data->stop_mutex);
    //stopped = data->simulation_stop;
    return (0);//stopped;
}

void print_status(t_philosopher *philo, const char *status)
{
    long long current_time;
    
    if (is_simulation_stopped(philo->data))
        return;
        
    pthread_mutex_lock(&philo->data->print_mutex);
    current_time = get_current_time() - philo->data->start_time;
    if (!is_simulation_stopped(philo->data))
        printf("%lld %d %s\n", current_time, philo->id, status);
    pthread_mutex_unlock(&philo->data->print_mutex);
}

void eat(t_philosopher *philo, t_data *data)
{
    pthread_mutex_lock(philo->left_fork);
    print_status(philo, "has taken a fork");
    /// death check
    pthread_mutex_lock(philo->right_fork);
    print_status(philo, "has taken a fork");
    /// death check
    
    pthread_mutex_lock(&philo->meal_mutex);
    philo->last_meal_time = get_current_time();
    philo->meals_eaten++;
    pthread_mutex_unlock(&philo->meal_mutex);
    
    print_status(philo, "is eating");
    smart_sleep(philo->data->time_to_eat, data);
    
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
}

// void *check_death(t_data *data)
// {
//     int i;
//     long long current_time;
    
//     while (!is_simulation_stopped(data))
//     {
//         i = 0;
//         while (i < data->number_of_philosophers)
//         {
//             current_time = get_current_time();
//             pthread_mutex_lock(&data->philosophers[i].meal_mutex);
//             if (current_time - data->philosophers[i].last_meal_time > data->time_to_die)
//             {
//                 print_status(&data->philosophers[i], "died");
//                 set_simulation_stop(data);
//                 pthread_mutex_unlock(&data->philosophers[i].meal_mutex);
//                 return NULL;
//             }
//             pthread_mutex_unlock(&data->philosophers[i].meal_mutex);
//             i++;
//         }
//         usleep(1000); 
//     }
//     return NULL;
// }