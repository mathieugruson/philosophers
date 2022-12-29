/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 16:43:12 by mgruson           #+#    #+#             */
/*   Updated: 2022/12/29 12:08:37 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_args	args;
	
	if (argc < 5 || argc > 6)
		return (printf("incorrect args nb\n"), 1);
	memset(&args, 0, sizeof(t_args));
	if (do_parsing(argv, argc, &args) == -1)
		return (printf("parsing error\n"), 1);
	return (0);
}