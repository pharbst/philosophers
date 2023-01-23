/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_exec_sim.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 10:19:27 by pharbst           #+#    #+#             */
/*   Updated: 2023/01/23 02:21:16 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

bool	create_threads(t_a *a)
{
	int	i;

	i = 0;
	while (i < a->parameter.philo_count)
	{
		if (pthread_create(&a->philo[i].thread, NULL, &philo_main, &a->philo[i]))
			return (true);
		i++;
	}
	if (pthread_create(&a->thread, NULL, &vitalmonitor, a))
		return (true);
	if (a->parameter.eat_count != -1)
		if (pthread_create(&a->thread2, NULL, &food_monitor, a))
			return (true);
	return (false);
}

bool	join_threads(t_a *a)
{
	int	i;

	i = 0;
	while (i < a->parameter.philo_count)
	{
		if (pthread_join(a->philo[i].thread, NULL))
			return (true);
		i++;
	}
	if (pthread_join(a->thread, NULL))
		return (true);
	if (a->parameter.eat_count != -1)
		if (pthread_join(a->thread2, NULL))
			return (true);
	return (false);
}

void	set_deathtime(t_a *a)
{
	int	i;

	i = 0;
	while (i < a->parameter.philo_count)
	{
		a->philo[i].deathtime = a->parameter.starttime
			+ a->parameter.time_to_die * 1000;
		i++;
	}
}

int	exec_sim(t_a *a)
{
	pthread_mutex_lock(&a->m_run);
	a->run = true;
	if (create_threads(a))
		return (1);
	usleep(100);
	*(unsigned long *)&a->parameter.starttime = utime();
	set_deathtime(a);
	pthread_mutex_unlock(&a->m_run);
	if (join_threads(a))
		return (2);
	return (false);
}
