/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 12:19:33 by mgruson           #+#    #+#             */
/*   Updated: 2023/01/03 12:00:03 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* 
This code converts a time value in seconds and microseconds
to a time value in milliseconds. The time value is stored in
the time struct, which has two fields: tv_sec and tv_usec.tv_sec
stores the time value in seconds, while tv_usec stores the time
value in microseconds.
*/

int	get_time(long long *ms)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (-1);
	*ms = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (0);
}
