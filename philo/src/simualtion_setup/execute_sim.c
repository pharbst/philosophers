/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_sim.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 07:06:17 by pharbst           #+#    #+#             */
/*   Updated: 2022/12/08 11:11:43 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

bool	execute_sim(t_a *a)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	(*(unsigned long *)&a->parameter.starttime) = tv.tv_sec * 1000000 + tv.tv_usec;
	printf("Simulation started with %d philosopers %dms needed to eat %dms needed to sleep %dms to die, each philo should eat %d times\n", a->philo_count, a->time_to_eat, a->time_to_sleep, a->time_to_die, a->eat_count);
	return (false);
}
