/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 16:38:50 by mgruson           #+#    #+#             */
/*   Updated: 2023/01/03 12:07:43 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

int	ft_atoi_philo(char *str)
{
	long	num;
	int		i;

	i = 0;
	num = 0;
	if (!str || !str[i] || ft_strlen(str) > 10)
		return (-1);
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + str[i] - 48;
		i++;
	}
	if (str[i])
		return (-1);
	if (num > INT_MAX)
		return (-1);
	return ((int)num);
}		

int	do_parsing(char **argv, int argc, t_arg *arg)
{
	arg->philo_num = ft_atoi_philo(argv[1]);
	arg->die_time = ft_atoi_philo(argv[2]);
	arg->eat_time = ft_atoi_philo(argv[3]);
	arg->sleep_time = ft_atoi_philo(argv[4]);
	if (get_time(&(arg->start_time)) == -1)
		return (-1);
	if (arg->philo_num <= 0 || arg->die_time == -1
		|| arg->eat_time == -1 || arg->sleep_time == -1)
		return (-1);
	if (argc == 6)
	{
		arg->must_eat = ft_atoi_philo(argv[5]);
		if (arg->must_eat < 0)
			return (-1);
	}
	else
		arg->must_eat = INT_MAX;
	return (0);
}
