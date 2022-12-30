/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 16:38:50 by mgruson           #+#    #+#             */
/*   Updated: 2022/12/30 13:45:59 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

int	ft_atoi(char *str)
{
	unsigned int	nb;
	int				i;

	i = 0;
	nb = 0;
	while (str && str[i] == '0')
		i++;
	if (!str || !str[i] || ft_strlen(&str[i]) > 10)
		return (-1);
	if (!(str[i] >= '1' && str[i] <= '9'))
		return (-1);
	while (str[i] >= '0' && str[i] <= '9')
		nb = nb * 10 + str[i++] - 48;
	if (str[i])
		return (-1);
	if (nb > INT_MAX)
		return (-1);
	return ((int)nb);
}		

int	do_parsing(char **argv, int argc, t_arg *arg)
{
	arg->philo_num = ft_atoi(argv[1]);
	arg->die_time = ft_atoi(argv[2]);
	arg->eat_time = ft_atoi(argv[3]);
	arg->sleep_time = ft_atoi(argv[4]);
	if (get_time(&(arg->start_time)) == -1)
		return (-1);
	if (arg->philo_num <= 0 || arg->die_time == -1
		|| arg->eat_time == -1 || arg->sleep_time == -1)
		return (-1);
	if (argc == 6)
	{
		arg->must_eat = ft_atoi(argv[5]);
		if (arg->must_eat <= 0)
			return (-1);
	}
	else
		arg->must_eat = INT_MAX;	
	if (TEST)
		printf("philo nb : %i, die %i, eat %i, sleep %i, must_eat %i\n", \
		arg->philo_num, arg->die_time, arg->eat_time, arg->sleep_time, arg->must_eat);
	return (0);
}