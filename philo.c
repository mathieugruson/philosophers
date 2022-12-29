/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 16:43:12 by mgruson           #+#    #+#             */
/*   Updated: 2022/12/29 20:54:40 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_arg	arg;
	t_philo	philo;
	
	if (argc < 5 || argc > 6)
		return (printf("incorrect arg nb\n"), -1);
	memset(&arg, 0, sizeof(t_arg));
	if (do_parsing(argv, argc, &arg) == -1)
		return (printf("parsing error\n"), -1);
	return (0);
}