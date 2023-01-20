/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 12:22:01 by pharbst           #+#    #+#             */
/*   Updated: 2023/01/20 01:55:53 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

bool	take_fork2(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		// pthread_mutex_lock(philo->m_run);
		// if (*(philo->run) == false)
			// return (true);
		pthread_mutex_lock(philo->left_fork);
		// pthread_mutex_lock(&philo->m_id);
		// printf("%lu %d took left fork\n", timestamp(philo->parameter.starttime), philo->id);
		// pthread_mutex_unlock(&philo->m_id);
		// pthread_mutex_unlock(philo->m_run);
	}
	else
	{
		// pthread_mutex_lock(philo->m_run);
		// if (*(philo->run) == false)
		// 	return (true);
		pthread_mutex_lock(philo->right_fork);
		// pthread_mutex_lock(&philo->m_id);
		// printf("%lu %d took right fork\n", timestamp(philo->parameter.starttime), philo->id);
		// pthread_mutex_unlock(&philo->m_id);
		// pthread_mutex_unlock(philo->m_run);
	}
	return (false);
}

bool	take_fork1(t_philo *philo)
{
	// pthread_mutex_lock(philo->m_run);
	// if (*(philo->run) == false)
	// 	return (true);
	// pthread_mutex_lock(&philo->m_id);
	// if (philo->id % 2 == 0)
	// {
	// 	pthread_mutex_lock(philo->right_fork);
	// 	printf("%lu %d took right fork", timestamp(philo->parameter.starttime), philo->id);
	// }
	// else
	// {
	// 	real_usleep(philo->parameter.time_to_eat);
	// }
	if (philo->id % 2 == 0)
	{
		// pthread_mutex_lock(philo->m_run);
		// if (*(philo->run) == false)
		// 	return (true);
		pthread_mutex_lock(philo->right_fork);
		// pthread_mutex_lock(&philo->m_id);
		// printf("%lu %d took right fork\n", timestamp(philo->parameter.starttime), philo->id);
		// pthread_mutex_unlock(&philo->m_id);
		// pthread_mutex_unlock(philo->m_run);
	}
	else
	{
		// pthread_mutex_lock(philo->m_run);
		// if (*(philo->run) == false)
		// 	return (true);
		pthread_mutex_lock(philo->left_fork);
		// pthread_mutex_lock(&philo->m_id);
		// printf("%lu %d took left fork\n", timestamp(philo->parameter.starttime), philo->id);
		// pthread_mutex_unlock(&philo->m_id);
		// pthread_mutex_unlock(philo->m_run);
	}
	return (take_fork2(philo));
}

void	*philo_main(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	pthread_mutex_lock(philo->m_run);
	pthread_mutex_lock(&philo->m_id);
	printf("%lu %d is thinking\n", timestamp(philo->parameter.starttime), philo->id);
	if (philo->id % 2 == 1)
	{
		pthread_mutex_unlock(&philo->m_id);
		pthread_mutex_unlock(philo->m_run);
		real_usleep(utime() + philo->parameter.time_to_eat * 1000);
	}
	while ((philo->parameter.eat_count == -1 || philo->eat_count < philo->parameter.eat_count) && *(philo->run) == true)
	{
		if (take_fork1(philo) == true)
			return (NULL);
		pthread_mutex_lock(philo->m_run);
		if (*(philo->run) == false)
			return (NULL);
		pthread_mutex_lock(&philo->m_deathtime);
		pthread_mutex_lock(&philo->m_id);
		printf("%lu %d is eating\n", timestamp(philo->parameter.starttime), philo->id);
		pthread_mutex_unlock(&philo->m_id);
		philo->deathtime = utime() + philo->parameter.time_to_die * 1000;
		pthread_mutex_unlock(&philo->m_deathtime);
		pthread_mutex_unlock(philo->m_run);
		real_usleep(utime() + philo->parameter.time_to_eat * 1000);
		pthread_mutex_lock(philo->m_run);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		if (*(philo->run) == false)
		{
			pthread_mutex_unlock(philo->m_run);
			return (NULL);
		}
		pthread_mutex_lock(&philo->m_id);
		printf("%lu %d is sleeping\n", timestamp(philo->parameter.starttime), philo->id);
		pthread_mutex_unlock(philo->m_run);
		pthread_mutex_unlock(&philo->m_id);
		real_usleep(utime() + philo->parameter.time_to_sleep * 1000);
		pthread_mutex_lock(philo->m_run);
		pthread_mutex_lock(&philo->m_id);
		printf("%lu %d is thinking\n", timestamp(philo->parameter.starttime), philo->id);
		pthread_mutex_unlock(&philo->m_id);
		pthread_mutex_unlock(philo->m_run);
	}
	pthread_mutex_unlock(philo->m_run);
	return (NULL);
}
