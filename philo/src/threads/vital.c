/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vital.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 11:43:41 by pharbst           #+#    #+#             */
/*   Updated: 2023/01/23 03:06:40 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_philo	*first_dietime(t_a *a)
{
	t_philo	*early;
	int		i;

	early = a->philo;
	i = 1;
	while (i < a->parameter.philo_count)
	{
		pthread_mutex_lock(&a->philo[i].m_deathtime);
		pthread_mutex_lock(&early->m_deathtime);
		if (a->philo[i].deathtime < early->deathtime)
		{
			pthread_mutex_unlock(&early->m_deathtime);
			early = &a->philo[i];
		}
		else
			pthread_mutex_unlock(&early->m_deathtime);
		pthread_mutex_unlock(&a->philo[i].m_deathtime);
		i++;
	}
	return (early);
}

void	death_check(t_a *a, t_philo *early)
{
	if (early->deathtime <= utime() && a->run == true)
	{
		printf("%lu %d died\n", timestamp(a->parameter.starttime),
			early->id);
		a->run = false;
		pthread_mutex_unlock(&a->m_run);
		pthread_mutex_unlock(&early->m_deathtime);
		return ;
	}
}

static bool	run_check(t_a *a)
{
	pthread_mutex_lock(&a->m_run);
	if (a->run == false)
	{
		pthread_mutex_unlock(&a->m_run);
		return (true);
	}
	pthread_mutex_unlock(&a->m_run);
	return (false);
}

void	*vitalmonitor(void *data)
{
	t_a				*a;
	t_philo			*early;
	unsigned long	time;

	a = (t_a *)data;
	while (1)
	{
		run_check(a);
		early = first_dietime(a);
		pthread_mutex_lock(&early->m_deathtime);
		time = early->deathtime;
		pthread_mutex_unlock(&early->m_deathtime);
		real_usleep(time);
		pthread_mutex_lock(&early->m_deathtime);
		pthread_mutex_lock(&a->m_run);
		death_check(a, early);
		pthread_mutex_unlock(&a->m_run);
		pthread_mutex_unlock(&early->m_deathtime);
	}
}
