/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 01:24:42 by pharbst           #+#    #+#             */
/*   Updated: 2023/01/23 02:18:07 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static bool philo_think(t_philo *philo)
{
	if (print_log(philo, "is thinking"))
		return (true);
	if (philo->parameter->philo_count % 2 == 1)
		real_usleep(utime() + philo->parameter->time_to_eat * 1000);
	return (false);
}

static bool	philo_eat(t_philo *philo)
{
	if (print_log(philo, "is eating"))
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);	
		return (true);
	}
	pthread_mutex_lock(&philo->m_deathtime);
	philo->deathtime = utime() + philo->parameter->time_to_die * 1000;
	pthread_mutex_unlock(&philo->m_deathtime);
	if (philo->parameter->eat_count != -1)
	{
		pthread_mutex_lock(&philo->m_eat_count);
		philo->eat_count++;
		pthread_mutex_unlock(&philo->m_eat_count);
	}
	real_usleep(utime() + philo->parameter->time_to_eat * 1000);
	return (false);
}

static bool	philo_sleep(t_philo *philo)
{
	pthread_mutex_lock(philo->m_run);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	if (*(philo->run) == false)
	{
		pthread_mutex_unlock(philo->m_run);
		return (true);
	}
	printf("%lu %d is sleeping\n", timestamp(philo->parameter->starttime), philo->id);
	pthread_mutex_unlock(philo->m_run);
	real_usleep(utime() + philo->parameter->time_to_sleep * 1000);
	return (false);
}

void	*philo_main(void *data)
{
	t_philo	*philo;

	philo = data;
	if (philo_think(philo))
		return (NULL);
	if (philo->id % 2 == 1)
		real_usleep(utime() + philo->parameter->time_to_eat * 1000);
	while (1)
	{
		if (take_fork(philo))
			return (NULL);
		if (philo_eat(philo))
			return (NULL);
		if (philo_sleep(philo))
			return (NULL);
		if (philo_think(philo))
			return (NULL);
	}
}
