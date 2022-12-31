/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 12:25:42 by mgruson           #+#    #+#             */
/*   Updated: 2022/12/31 15:33:09 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_thread(t_arg *arg, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < arg->philo_num)
		pthread_mutex_destroy(&(arg->forks[i++]));
	free(philo);
	free(arg->forks);
	pthread_mutex_destroy(&(arg->stop_mutex));
	pthread_mutex_destroy(&(arg->finished_eat_mutex));
	pthread_mutex_destroy(&(arg->print_mutex));
}