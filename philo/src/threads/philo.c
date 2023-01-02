/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peter <peter@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 12:22:01 by pharbst           #+#    #+#             */
/*   Updated: 2023/01/02 23:45:19 by peter            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// static int	philo_sleep(unsigned int wakeuptime, unsigned long deathtime)
// {
// 	unsigned long	actualtime;
// 	struct timeval	tv;

// 	if (wakeuptime > deathtime)
// 		wakeuptime = deathtime;
// 	gettimeofday(&tv, NULL);
// 	actualtime = tv.tv_sec * 1000000 + tv.tv_usec;
// 	while(actualtime < wakeuptime)
// 	{
// 		usleep(1);
// 		gettimeofday(&tv, NULL);
// 		actualtime = tv.tv_sec * 1000000 + tv.tv_usec;
// 	}
// 	if (wakeuptime == deathtime)
// 		return (1);
// 	return (0);
// }

bool	take_fork2(t_philo philo)
{
	if (philo.id % 2 == 0)
	{
		pthread_mutex_lock(philo.m_run);
		if (*(philo.run) == true)
		{
			pthread_mutex_lock(philo.left_fork);
			printf("==%lu==	philo%d took left fork\n", timestamp(philo.parameter.starttime));
			pthread_mutex_lock(philo.m_run);
		}
		else
			return (true);
	}
	else
	{
		pthread_mutex_lock(philo.m_run);
		if (*(philo.run) == true)
		{
			pthread_mutex_lock(philo.right_fork);
			printf("==%lu==	philo%d took right fork\n", timestamp(philo.parameter.starttime));
			pthread_mutex_lock(philo.m_run);
		}
		else
			return (true);
	}
	return (false);
}

bool	take_fork1(t_philo philo)
{
	if (philo.id % 2 == 0)
	{
		pthread_mutex_lock(philo.m_run);
		if (*(philo.run) == false)
			return (true);
		pthread_mutex_lock(philo.right_fork);
		printf("==%lu==	philo%d took right fork\n", timestamp(philo.parameter.starttime));
		pthread_mutex_unlock(philo.m_run);
	}
	else
	{
		pthread_mutex_lock(philo.m_run);
		if (*(philo.run) == true)
		{
			pthread_mutex_lock(philo.left_fork);
			printf("==%lu==	philo%d took left fork\n", timestamp(philo.parameter.starttime));
			pthread_mutex_unlock(philo.m_run);
		}
		else
			return (true);
	}
	return (take_fork2(philo));
}

void	philo(t_philo philo)
{
	pthread_mutex_lock(philo.m_run);
	while ((philo.parameter.eat_count == -1 || philo.eat_count < philo.parameter.eat_count) && *(philo.run) == true)
	{
		pthread_mutex_lock(&philo.m_id);
		printf("==%lu==	philo%d is thinking", timestamp(philo.parameter.starttime), philo.id);
		pthread_mutex_unlock(&philo.m_id);
		pthread_mutex_unlock(philo.m_run);
		if (take_fork1 == true)
			return ;
		pthread_mutex_lock(philo.m_run);
		if (*(philo.run) == false)
			return ;
		pthread_mutex_lock(&philo.m_deathtime);
		pthread_mutex_lock(&philo.m_id);
		printf("==%lu==	philo%d is eating\n", timestamp(philo.parameter.starttime), philo.id);
		pthread_mutex_unlock(&philo.m_id);
		philo.deathtime = utime() + philo.parameter.time_to_die * 1000;
		pthread_mutex_unlock(&philo.m_deathtime);
		pthread_mutex_unlock(philo.m_run);
		real_usleep(utime() + philo.parameter.time_to_eat * 1000);
		pthread_mutex_unlock(philo.left_fork);
		pthread_mutex_unlock(philo.right_fork);
		pthread_mutex_lock(philo.m_run);
		if (*(philo.run) == false)
			return ;
		pthread_mutex_lock(&philo.m_id);
		printf("==%lu==	philo%d is sleeping", timestamp(philo.parameter.starttime), philo.id);
		pthread_mutex_unlock(philo.m_run);
		pthread_mutex_unlock(&philo.m_id);
		real_usleep(utime() + philo.parameter.time_to_sleep * 1000);
		pthread_mutex_lock(philo.m_run);
	}
}
