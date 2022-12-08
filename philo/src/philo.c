/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 12:22:01 by pharbst           #+#    #+#             */
/*   Updated: 2022/12/08 11:42:17 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	philo_sleep(unsigned int wakeuptime, unsigned long deathtime)
{
	unsigned long	actualtime;
	struct timeval	tv;

	if (wakeuptime > deathtime)
		wakeuptime = deathtime;
	while(actualtime < wakeuptime)
	{
		usleep(1);
		gettimeofday(&tv, NULL);
	}
	if (wakeuptime = deathtime)
		return (1);
	return (0);
}

void	philo(t_philo philo)
{
	while (philo.alive == true)
	{
		printf("==%d==	philo%d is thinking", timestamp(philo.parameter.starttime), philo.id);
		if (philo.id % 2 == 0)
			pthread_mutex_lock(philo.right_fork);
		else
			pthread_mutex_lock(philo.left_fork);
		if (philo.id % 2 == 0)
			pthread_mutex_lock(philo.left_fork);
		else
			pthread_mutex_lock(philo.right_fork);
		philo.deathtime = utime() + philo.parameter.time_to_die * 1000;
		if (philo_sleep(utime() + philo.parameter.time_to_eat * 1000, philo.deathtime))
			return (philo.alive = false, 1);
		printf("==%d==	philo%d is sleeping", timestamp(philo.parameter.starttime), philo.id);
		if (philo_sleep(utime() + philo.parameter.time_to_sleep ))
	}
}
