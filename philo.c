/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 16:43:12 by mgruson           #+#    #+#             */
/*   Updated: 2022/12/30 21:02:08 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_printf(t_arg *arg, int philo_id, char *msg)
{
	long long time;
	
	if (get_time(&time) == -1)
		return (-1);
	pthread_mutex_lock(&(arg->print));
	pthread_mutex_lock(&(arg->finish_mutex));
	if (!arg->finish)
	{
		printf("%lld %d %s\n", get_time_in_ms() - arg->start_time, philo_id + 1, msg);
		pthread_mutex_unlock(&(arg->finish_mutex));	
	}
	else
		pthread_mutex_unlock(&(arg->finish_mutex));	
	pthread_mutex_unlock(&(arg->print));
	pthread_mutex_lock(&(arg->finish_mutex));
	if(arg->finish)
	{
		pthread_mutex_unlock(&(arg->finish_mutex));	
		return (-1);
	}
	else
		pthread_mutex_unlock(&(arg->finish_mutex));	
	return (0);
}

int	is_dead(t_philo *philo, t_arg *arg)
{
	long long now;

	// if (get_time(&now) == -1)
	// 	return (-1);	
	if ((get_time_in_ms() - philo->last_eat_time) > (long long)arg->die_time)
	{
		if (philo_printf(arg, philo->id, "die") == -1)
			return (-1);
		pthread_mutex_lock(&(arg->finish_mutex));
		arg->finish = 1;
		pthread_mutex_unlock(&(arg->finish_mutex));	
		return (1);
	}
	return (0);
}

int	pass_time(long long eat_time, t_arg *arg, t_philo *philo)
{
	long long	start;
	long long	now;

	if (get_time(&start) == -1)
		return (-1);
	while ((get_time_in_ms() - start) < eat_time)
	{
		// if (get_time(&now) == -1)
		// 	return (-1);
		if (is_dead(philo, arg))
			return (-1);		
		pthread_mutex_lock(&(arg->finish_mutex));
		if (arg->finish == 1)
		{	
			pthread_mutex_unlock(&(arg->finish_mutex));
			return (-1);
		}
		else 
			pthread_mutex_unlock(&(arg->finish_mutex));

	}
}

void *ft_thread(void *argv)
{
	t_arg	*arg;
	t_philo *philo;

	philo = argv;
	arg = philo->arg;
	if (philo->id % 2)
		usleep(1000);
	else
		usleep(500);
	while (philo->eat_count < arg->must_eat && !is_dead(philo, arg))
	{

		pthread_mutex_lock(&(arg->forks[philo->left]));
		if (!is_dead(philo, arg))
			philo_printf(arg, philo->id, "has taken left fork");
		if (arg->philo_num != 1)
		{

			pthread_mutex_lock(&(arg->forks[philo->right]));
			if (!is_dead(philo, arg))
			{
				if (philo_printf(arg, philo->id, "has taken right fork") == -1)
				{
					pthread_mutex_unlock(&(arg->forks[philo->right]));
					pthread_mutex_unlock(&(arg->forks[philo->left]));	
					break;
				}
			}
			if (get_time(&(philo->last_eat_time)) == -1)
				break;
			if (!is_dead(philo, arg))
			{
				if (philo_printf(arg, philo->id, "is eating") == -1)
				{
					pthread_mutex_unlock(&(arg->forks[philo->right]));
					pthread_mutex_unlock(&(arg->forks[philo->left]));	
					break;
				}
			}

			philo->eat_count++;
			if (pass_time((long long)arg->eat_time, arg, philo) == -1)
			{
				pthread_mutex_unlock(&(arg->forks[philo->right]));
				pthread_mutex_unlock(&(arg->forks[philo->left]));
				break;
			}
			pthread_mutex_unlock(&(arg->forks[philo->right]));
			pthread_mutex_unlock(&(arg->forks[philo->left]));
			if (philo_printf(arg, philo->id, "is sleeping") == -1)
				break;			
			if (pass_time((long long)arg->sleep_time, arg, philo) == -1)
				break;
			if (philo_printf(arg, philo->id, "is thinking") == -1)
				break;
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
		if (pthread_create(&(philo[i].thread), NULL, ft_thread, &(philo[i])))
			return (-1);
		i++;
	}
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