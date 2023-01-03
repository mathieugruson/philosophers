/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 16:43:12 by mgruson           #+#    #+#             */
/*   Updated: 2023/01/03 12:27:38 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_printf(t_arg *arg, int id, char *msg)
{
	long long	now;

	if (get_time(&now) == -1)
		return (-1);
	pthread_mutex_lock(&(arg->print_mutex));
	pthread_mutex_lock(&(arg->stop_mutex));
	if (!(arg->stop))
	{
		printf("%lld %d %s\n", now - arg->start_time, id + 1, msg);
	}
	pthread_mutex_unlock(&(arg->stop_mutex));
	pthread_mutex_unlock(&(arg->print_mutex));
	return (0);
}

int	pass_time(long long wait_time, t_arg *arg)
{
	long long	start;
	long long	now;

	if (get_time(&start) == -1)
		return (-1);
	while (1)
	{
		pthread_mutex_lock(&(arg->stop_mutex));
		if (!(arg->stop))
		{
			pthread_mutex_unlock(&(arg->stop_mutex));
			if (get_time(&now) == -1)
				return (-1);
			if ((now - start) >= wait_time)
				return (usleep(10), -1);
			if (wait_time == 0)
				return (usleep(100), -1);
			usleep(10);
		}
		else
		{
			pthread_mutex_unlock(&(arg->stop_mutex));
			break ;
		}
	}
}

int	start_dinner(t_arg *arg, t_philo *philo)
{
	int		i;

	i = 0;
	while (i < arg->philo_num)
	{	
		if (get_time(&philo[i].last_eat_time) == -1)
			return (-1);
		if (pthread_create(&(philo[i].thread), 0, dinner_thread, &(philo[i])))
			return (-1);
		i++;
	}
	stop_dinner(arg, philo);
	i = 0;
	while (i < arg->philo_num)
	{
		pthread_join(philo[i++].thread, NULL);
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_arg	arg;
	t_philo	*philo;

	if (argc < 5 || argc > 6)
		return (printf("incorrect arg nb\n"), -1);
	memset(&arg, 0, sizeof(t_arg));
	if (do_parsing(argv, argc, &arg) == -1)
		return (printf("parsing error\n"), -1);
	if (init_mutex(&arg) == -1)
		return (printf("init mutex failed"), -1);
	if (init_philo_struct(&philo, &arg) == -1)
		return (printf("init philo struct failed\n"), -1);
	if (start_dinner(&arg, philo) == -1)
		return (printf("dinner failed\n"), -1);
	free_malloc_and_mutex(&arg, philo);
	return (0);
}
