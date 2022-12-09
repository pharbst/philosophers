/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 12:22:01 by pharbst           #+#    #+#             */
/*   Updated: 2022/12/09 09:30:37 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	philo_sleep(unsigned int wakeuptime, unsigned long deathtime)
{
	unsigned long	actualtime;
	struct timeval	tv;

	if (wakeuptime > deathtime)
		wakeuptime = deathtime;
	gettimeofday(&tv, NULL);
	actualtime = tv.tv_sec * 1000000 + tv.tv_usec;
	while(actualtime < wakeuptime)
	{
		usleep(1);
		gettimeofday(&tv, NULL);
		actualtime = tv.tv_sec * 1000000 + tv.tv_usec;
	}
	if (wakeuptime == deathtime)
		return (1);
	return (0);
}

void	philo(t_philo philo)
{
	while (philo.alive == true && (philo.parameter.eat_count == -1 || philo.eat_count < philo.parameter.eat_count))
	{
		printf("==%lu==	philo%d is thinking", timestamp(philo.parameter.starttime), philo.id);
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
		{
			pthread_mutex_lock(&philo.m_alive);
			philo.alive = false;
			pthread_mutex_unlock(&philo.m_alive);
			return ;
		}
		printf("==%lu==	philo%d is sleeping", timestamp(philo.parameter.starttime), philo.id);
		if (philo_sleep(utime() + philo.parameter.time_to_sleep, philo.deathtime))
		{
			pthread_mutex_lock(&philo.m_alive);
			philo.alive = false;
			pthread_mutex_unlock(&philo.m_alive);
			return ;
		}
	}
}
