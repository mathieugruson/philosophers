/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 16:38:50 by mgruson           #+#    #+#             */
/*   Updated: 2022/12/29 12:08:47 by mgruson          ###   ########.fr       */
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

int	do_parsing(char **argv, int argc, t_args *args)
{
	args->philo_nb = ft_atoi(argv[1]);
	args->die_time = ft_atoi(argv[2]);
	args->eat_time = ft_atoi(argv[3]);
	args->sleep_time = ft_atoi(argv[4]);
	if (args->philo_nb <= 0 || args->die_time == -1
		|| args->eat_time == -1 || args->sleep_time == -1)
		return (-1);
	if (argc == 6)
	{
		args->must_eat = ft_atoi(argv[5]);
		if (args->must_eat <= 0)
			return (-1);
	}	
	if (TEST)
		printf(" philo nb : %i, die %i, eat %i, sleep %i, must_eat %i\n", \
		args->philo_nb, args->die_time, args->eat_time, args->sleep_time, args->must_eat);
	return (0);
}