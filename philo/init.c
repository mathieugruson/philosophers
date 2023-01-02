/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 12:15:55 by mgruson           #+#    #+#             */
/*   Updated: 2023/01/02 18:58:10 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

int	init_mutex(t_arg *arg)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&(arg->finished_eat_mutex), NULL))
		return (-1);
	if (pthread_mutex_init(&(arg->stop_mutex), NULL))
		return (-1);
	if (pthread_mutex_init(&(arg->print_mutex), NULL))
		return (-1);
	arg->forks = malloc(sizeof(pthread_mutex_t) * arg->philo_num);
	if (!(arg->forks))
		return (-1);
	while (i < arg->philo_num)
	{
		if (pthread_mutex_init(&(arg->forks[i]), NULL))
			return (-1);
		i++;
	}
	arg->last_eat_time_mutex = malloc(sizeof(pthread_mutex_t) * arg->philo_num);
	if (!(arg->last_eat_time_mutex))
		return (-1);
	i = 0;
	while (i < arg->philo_num)
	{
		if (pthread_mutex_init(&(arg->last_eat_time_mutex[i]), NULL))
			return (-1);
		i++;
	}
	return (0);
}

int	init_philo_struct(t_philo **philo, t_arg *arg)
{
	int	i;

	i = 0;
	*philo = malloc(sizeof(t_philo) * arg->philo_num);
	if (!(philo))
		return (-1);
	while (i < arg->philo_num)
	{
		(*philo)[i].arg = arg;
		(*philo)[i].id = i;
		(*philo)[i].left = i;
		(*philo)[i].right = (i + 1) % arg->philo_num; // idem
		if ((*philo)[i].id % 2)
		{
			(*philo)[i].left = ((*philo)[i].id + 1) % arg->philo_num; // a appronfondir
			(*philo)[i].right = (*philo)[i].id;
		}
		(*philo)[i].last_eat_time = 0;
		(*philo)[i].eat_count = 0;
		i++;
	}
	return (0);
}