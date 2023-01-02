/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 12:42:40 by mgruson           #+#    #+#             */
/*   Updated: 2023/01/02 21:33:24 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H 

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
# include <sys/time.h>
#include <limits.h>

typedef struct s_philo
{
	struct s_arg	*arg;
	pthread_t		thread;
	int				id;
	int				left;
	int				right;
	long long		last_eat_time;
	int				eat_count;
}				t_philo;

typedef struct s_arg
{
	int				philo_num;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				must_eat;
	long long		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	int				stop;
	pthread_mutex_t	stop_mutex;
	int				finished_eat;
	pthread_mutex_t	finished_eat_mutex;
	pthread_mutex_t	*last_eat_time_mutex;
}	t_arg;

int	do_parsing(char **argv, int argc, t_arg *arg);

/* init.c */

int	init_mutex(t_arg *arg);
int	init_philo_struct(t_philo **philo, t_arg *arg);

/* time.c */

int		get_time(long long *ms);
time_t	get_time_in_ms(void);

/* free.c */

void	free_malloc_and_mutex(t_arg *arg, t_philo *philo);

/* stop_dinner.c */

void	stop_dinner(t_arg *arg, t_philo *philo);

#endif