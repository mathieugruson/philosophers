/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 12:40:07 by mgruson           #+#    #+#             */
/*   Updated: 2022/12/20 12:58:27 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void*	routine(void)
{
    printf("test\n");
}

int main(int argc, char *argv[])
{ 
    (void)argc;
    (void)argv; 
    pthread_t t1;
    
	pthread_create(&t1, NULL, (void *)routine, NULL);
    pthread_join(t1, NULL);
    return (0);    
}