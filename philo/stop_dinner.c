/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stop_dinner.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 21:32:15 by mgruson           #+#    #+#             */
/*   Updated: 2023/01/03 12:02:00 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	last_eat_time_is_higher_than_die_time(t_arg *arg, t_philo *philo, int i)
{
	long long	now;

	while (i < arg->philo_num)
	{
		if (get_time(&now) == -1)
			return (-1);
		pthread_mutex_lock(&(arg->last_eat_time_mutex[i]));
		if ((now - philo[i].last_eat_time) >= arg->die_time)
		{
			pthread_mutex_unlock(&(arg->last_eat_time_mutex[i]));
			philo_printf(arg, i, "died");
			pthread_mutex_lock(&(arg->stop_mutex));
			arg->stop = 1;
			pthread_mutex_unlock(&(arg->stop_mutex));
			return (-1);
		}
		else
			pthread_mutex_unlock(&(arg->last_eat_time_mutex[i]));
		i++;
	}
}

int	all_philo_have_finished_to_eat(t_arg *arg, t_philo *philo)
{
	pthread_mutex_unlock(&(arg->stop_mutex));
	pthread_mutex_lock(&(arg->finished_eat_mutex));
	if ((arg->must_eat != INT_MAX) && (arg->philo_num == arg->finished_eat))
	{
		pthread_mutex_unlock(&(arg->finished_eat_mutex));
		pthread_mutex_lock(&(arg->stop_mutex));
		arg->stop = 1;
		pthread_mutex_unlock(&(arg->stop_mutex));
		return (-1);
	}
	else
		pthread_mutex_unlock(&(arg->finished_eat_mutex));
	return (0);
}

void	stop_dinner(t_arg *arg, t_philo *philo)
{
	int			i;

	while (1)
	{
		pthread_mutex_lock(&(arg->stop_mutex));
		if (!arg->stop)
		{
			if (all_philo_have_finished_to_eat(arg, philo) == -1)
				break ;
			i = 0;
			if (last_eat_time_is_higher_than_die_time(arg, philo, i) == -1)
				break ;
		}
		else
		{
			pthread_mutex_unlock(&(arg->stop_mutex));
			break ;
		}
		usleep(100);
	}
}
