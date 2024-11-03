/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfellahi <sfellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 11:08:18 by sfellahi          #+#    #+#             */
/*   Updated: 2024/11/03 14:53:56 by sfellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdbool.h>
# include <limits.h>

typedef struct s_philosopher
{
	int				id;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct s_data	*data;
	long long		last_meal_time;
	int				meals_eaten;
	pthread_mutex_t	meal_mutex;
}	t_philosopher;

typedef struct s_data
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	long long		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	stop_mutex;
	t_philosopher	*philosophers;
	bool			simulation_stop;
}	t_data;

int			init_data(t_data *data);
void		start_simulation(t_data *data);
void		cleanup(t_data *data);
bool	ft_is_overflow(const char *str);
long long	get_current_time(void);
void		smart_sleep(long long duration, t_data *data);
int			init_philosophers(t_data *data);
// int			ft_atoi(const char *str);
long long	ft_atoll(const char *str);
// void		smart_sleep(long long duration);
void		*philosopher_routine(void *arg);
int			init_mutexes(t_data *data);
void		set_simulation_stop(t_data *data);
bool		is_simulation_stopped(t_data *data);
void		print_status(t_philosopher *philo, const char *status);
void		check_death(t_data *data);
void		eat(t_philosopher *philo, t_data *data);
void		ft_putstr_fd(char *str, int fd);

#endif
