/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_thread.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 11:17:40 by mgruson           #+#    #+#             */
/*   Updated: 2023/01/03 12:06:09 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_take_forks(t_arg *arg, t_philo *philo)
{
	pthread_mutex_lock(&(arg->forks[philo->left]));
	philo_printf(arg, philo->id, "has taken a fork");
	if (arg->philo_num != 1)
	{
		pthread_mutex_lock(&(arg->forks[philo->right]));
		philo_printf(arg, philo->id, "has taken a fork");
		philo_printf(arg, philo->id, "is eating");
		pthread_mutex_lock(&(arg->last_eat_time_mutex[philo->id]));
		if (get_time(&(philo->last_eat_time)) == -1)
			return (-1);
		pthread_mutex_unlock(&(arg->last_eat_time_mutex[philo->id]));
		philo->eat_count = philo->eat_count + 1;
		pass_time((long long)arg->eat_time, arg);
		pthread_mutex_unlock(&(arg->forks[philo->right]));
	}
	else
		pass_time((long long)arg->die_time, arg);
	pthread_mutex_unlock(&(arg->forks[philo->left]));
}

int	philo_have_finished_to_eat(t_arg *arg, t_philo *philo)
{
	if (arg->must_eat == philo->eat_count)
	{
		pthread_mutex_lock(&(arg->finished_eat_mutex));
		arg->finished_eat++;
		pthread_mutex_unlock(&(arg->finished_eat_mutex));
		return (-1);
	}
	return (0);
}

void	philo_wait_to_avoid_deadlock(t_philo *philo)
{
	if (philo->id % 2)
		usleep(1000);
	else
		usleep(500);
}

void	*dinner_thread(void *argv)
{
	t_arg	*arg;
	t_philo	*philo;

	philo = argv;
	arg = philo->arg;
	philo_wait_to_avoid_deadlock(philo);
	while (1)
	{
		pthread_mutex_lock(&(arg->stop_mutex));
		if (!arg->stop)
		{
			pthread_mutex_unlock(&(arg->stop_mutex));
			if (philo_take_forks(arg, philo) == -1)
				break ;
			if (philo_have_finished_to_eat(arg, philo) == -1)
				break ;
			philo_printf(arg, philo->id, "is sleeping");
			pass_time((long long)arg->sleep_time, arg);
			philo_printf(arg, philo->id, "is thinking");
		}
		else
			return (pthread_mutex_unlock(&(arg->stop_mutex)), (int *)0);
	}
	return ((int *)0);
}
