/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 12:19:33 by mgruson           #+#    #+#             */
/*   Updated: 2022/12/30 13:21:56 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_time(long long *ms)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (-1);
	*ms = (time.tv_sec * 1000) + (time.tv_usec / 1000); // a appronfondir
	return (0); 
}
