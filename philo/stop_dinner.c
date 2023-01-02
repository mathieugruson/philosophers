/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stop_dinner.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 21:32:15 by mgruson           #+#    #+#             */
/*   Updated: 2023/01/02 21:34:30 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	stop_dinner(t_arg *arg, t_philo *philo)
{
	int			i;
	long long	now;

	while(1)
	{
		pthread_mutex_lock(&(arg->stop_mutex));
		if (!arg->stop)
		{
			pthread_mutex_unlock(&(arg->stop_mutex));
			pthread_mutex_lock(&(arg->finished_eat_mutex));
			if ((arg->must_eat != INT_MAX) && (arg->philo_num == arg->finished_eat))
			{
				pthread_mutex_unlock(&(arg->finished_eat_mutex));
				pthread_mutex_lock(&(arg->stop_mutex));
				arg->stop = 1;
				pthread_mutex_unlock(&(arg->stop_mutex));
				break ;
			}
			else
				pthread_mutex_unlock(&(arg->finished_eat_mutex));
			i = 0;
			while (i < arg->philo_num)
			{
				if (get_time(&now) == -1)
					break ;
				pthread_mutex_lock(&(arg->last_eat_time_mutex[i]));
				if ((now - philo[i].last_eat_time) >= arg->die_time)
				{
					pthread_mutex_unlock(&(arg->last_eat_time_mutex[i]));
					philo_printf(arg, i, "died");
					pthread_mutex_lock(&(arg->stop_mutex));
					arg->stop = 1;
					pthread_mutex_unlock(&(arg->stop_mutex));
					break ;
				}
				else
					pthread_mutex_unlock(&(arg->last_eat_time_mutex[i]));
				i++;
			}
		}
		else
		{
			pthread_mutex_unlock(&(arg->stop_mutex));
			break ;
		}
		usleep(1000);
	}
}
