/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 12:25:42 by mgruson           #+#    #+#             */
/*   Updated: 2023/01/03 11:55:58 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_malloc_and_mutex(t_arg *arg, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < arg->philo_num)
		pthread_mutex_destroy(&(arg->forks[i++]));
	i = 0;
	while (i < arg->philo_num)
		pthread_mutex_destroy(&(arg->last_eat_time_mutex[i++]));
	free(philo);
	free(arg->forks);
	free(arg->last_eat_time_mutex);
	pthread_mutex_destroy(&(arg->stop_mutex));
	pthread_mutex_destroy(&(arg->finished_eat_mutex));
	pthread_mutex_destroy(&(arg->print_mutex));
}
