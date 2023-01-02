/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 16:43:12 by mgruson           #+#    #+#             */
/*   Updated: 2023/01/02 16:13:28 by mgruson          ###   ########.fr       */
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
				return (-1);
			usleep(10);
		}
		else
		{
			pthread_mutex_unlock(&(arg->stop_mutex));
			break ;
		}
	}
}

void *dinner_thread(void *argv)
{
	t_arg	*arg;
	t_philo *philo;

	philo = argv;
	arg = philo->arg;
	if (philo->id % 2)
		usleep(1000);
	else
		usleep(500);
	while (1)
	{
		pthread_mutex_lock(&(arg->stop_mutex));
		if (!arg->stop)
		{
			pthread_mutex_unlock(&(arg->stop_mutex));
			pthread_mutex_lock(&(arg->forks[philo->left]));
			philo_printf(arg, philo->id, "has taken a fork");
			if (arg->philo_num != 1)
			{
				pthread_mutex_lock(&(arg->forks[philo->right]));
				philo_printf(arg, philo->id, "has taken a fork");
				philo_printf(arg, philo->id, "is eating");
				pthread_mutex_lock(&(arg->last_eat_time_mutex[philo->id]));
				if (get_time(&(philo->last_eat_time)) == -1)
					break ;
				pthread_mutex_unlock(&(arg->last_eat_time_mutex[philo->id]));
				philo->eat_count = philo->eat_count + 1;
				pass_time((long long)arg->eat_time, arg);
				pthread_mutex_unlock(&(arg->forks[philo->right]));
			}
			else
				pass_time((long long)arg->die_time, arg);
			pthread_mutex_unlock(&(arg->forks[philo->left]));
			if (arg->must_eat == philo->eat_count)
			{
				pthread_mutex_lock(&(arg->finished_eat_mutex));
				arg->finished_eat++;
				pthread_mutex_unlock(&(arg->finished_eat_mutex));
				break ;
			}
			philo_printf(arg, philo->id, "is sleeping");
			pass_time((long long)arg->sleep_time, arg);
			philo_printf(arg, philo->id, "is thinking");
		}
		else
		{
			pthread_mutex_unlock(&(arg->stop_mutex));
			break ;
		}
	}
	return (0);
}

void	check_philo_death(t_arg *arg, t_philo *philo)
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
				pthread_mutex_lock(&(arg->stop_mutex));
				arg->stop = 1;
				pthread_mutex_lock(&(arg->stop_mutex));
				break ;
			}
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
	}
}

int	start_dinner(t_arg *arg, t_philo *philo)
{
	int		i;

	i = 0;
	while (i < arg->philo_num)
	{	
		if (get_time(&philo[i].last_eat_time) == -1) // time au debut de la simulation
			return (-1); 
		if (pthread_create(&(philo[i].thread), NULL, dinner_thread, &(philo[i])))
			return (-1);
		i++;
	}
	check_philo_death(arg, philo);
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
	if (start_dinner(&arg, philo))
		return (printf("dinner failed\n"), -1);
	free_thread(&arg, philo);
	return (0);
}