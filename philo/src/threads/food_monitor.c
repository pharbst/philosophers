/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   food_monitor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 10:37:13 by pharbst           #+#    #+#             */
/*   Updated: 2023/01/21 13:36:55 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*food_monitor(void *data)
{
	t_a		*a;
	int		i;

	a = (t_a *)data;
	i = 0;
	while (1)
	{
		pthread_mutex_lock(&a->m_run);
		if (a->run == false)
		{
			pthread_mutex_unlock(&a->m_run);
			return (NULL);
		}
		pthread_mutex_unlock(&a->m_run);
		pthread_mutex_lock(&a->philo[i].m_eat_count);
		if (a->philo[i].eat_count == a->parameter.eat_count)
			i++;
		pthread_mutex_unlock(&a->philo[i].m_eat_count);
		if (i == a->parameter.philo_count)
			break ;
		usleep(100);
	}
	pthread_mutex_lock(&a->m_run);
	a->run = false;
	pthread_mutex_unlock(&a->m_run);
	return (NULL);
}
