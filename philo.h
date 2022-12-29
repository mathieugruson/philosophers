/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 12:42:40 by mgruson           #+#    #+#             */
/*   Updated: 2022/12/29 20:54:52 by mgruson          ###   ########.fr       */
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

#define TEST 1

typedef struct s_arg
{
	int				philo_nb;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				must_eat;
}	t_arg;

int	do_parsing(char **argv, int argc, t_arg *arg);

#endif