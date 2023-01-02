/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_sim.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peter <peter@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 07:06:17 by pharbst           #+#    #+#             */
/*   Updated: 2023/01/03 00:32:10 by peter            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

bool	execute_sim(t_a *a)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	(*(unsigned long *)&a->parameter.starttime) = tv.tv_sec * 1000000 + tv.tv_usec;
	printf("==%lu==	\n", timestamp(a->parameter.starttime));
	printf("sleepfunction test wait for %d ms\n", a->parameter.time_to_eat);
	real_usleep(utime() + a->parameter.time_to_eat * 1000);
	printf("==%lu==	\n", timestamp(a->parameter.starttime));
	printf("input values\n");
	printf("Simulation started with %d philosopers %dms needed to eat %dms needed to sleep %dms to die, each philo should eat %d times\n", a->parameter.philo_count, a->parameter.time_to_eat, a->parameter.time_to_sleep, a->parameter.time_to_die, a->parameter.eat_count);
	printf("atm no simulation\n");
	return (false);
}
