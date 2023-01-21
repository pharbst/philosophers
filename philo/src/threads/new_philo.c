/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 01:24:42 by pharbst           #+#    #+#             */
/*   Updated: 2023/01/21 07:38:32 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static bool philo_think(t_philo *philo)
{
	if (print_log(philo, "is thinking"))
		return (true);
	return (false);
}

static bool	philo_eat(t_philo *philo)
{
	if (print_log(philo, "is eating"))
		return (true);
	real_usleep(utime() + philo->parameter.time_to_eat * 1000);
	return (false);
}

static bool	philo_sleep(t_philo *philo)
{
	pthread_mutex_lock(philo->m_run);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	if (*(philo->run) == false)
		return (true);
	printf("%lu %d is sleeping\n", timestamp(philo->parameter.starttime), philo->id);
	pthread_mutex_unlock(philo->m_run);
	real_usleep(utime() + philo->parameter.time_to_sleep * 1000);
	return (false);
}

void	*philo_main(void *data)
{
	t_philo	*philo;

	philo = data;
	if (philo_think(philo))
		return (NULL);
	if (philo->id % 2 == 1)
		real_usleep(utime() + philo->parameter.time_to_eat * 1000);
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
