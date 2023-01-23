/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   food_monitor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 10:37:13 by pharbst           #+#    #+#             */
/*   Updated: 2023/01/23 13:27:55 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static bool	food_checker(t_a *a)
{
	int	i;

	i = 0;
	while (1)
	{
		if (run_check(&a->m_run, &a->run))
			return (true);
		pthread_mutex_lock(&a->philo[i].m_eat_count);
		if (a->philo[i].eat_count == a->parameter.eat_count)
		{
			pthread_mutex_unlock(&a->philo[i].m_eat_count);
			i++;
		}
		pthread_mutex_unlock(&a->philo[i].m_eat_count);
		if (i == a->parameter.philo_count)
			return (false);
		usleep(100);
	}
}

void	*food_monitor(void *data)
{
	t_a		*a;

	a = (t_a *)data;
	if (food_checker(a))
		return (NULL);
	pthread_mutex_lock(&a->m_run);
	a->run = false;
	pthread_mutex_unlock(&a->m_run);
	return (NULL);
}
