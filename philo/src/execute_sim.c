/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_sim.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 07:06:17 by pharbst           #+#    #+#             */
/*   Updated: 2022/12/05 07:13:33 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	execute_sim(t_a *a)
{
	printf("Simulation started with %d philosopers %dms needed to eat %dms needed to sleep %dms to die, each philo should eat %d times\n", a->philo_count, a->time_to_eat, a->time_to_sleep, a->time_to_die, a->eat_count);
	return (false);
}
