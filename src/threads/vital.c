/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vital.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 11:43:41 by pharbst           #+#    #+#             */
/*   Updated: 2023/01/23 13:43:15 by pharbst          ###   ########.fr       */
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
	pthread_mutex_lock(&early->m_deathtime);
	pthread_mutex_lock(&a->m_run);
	if (early->deathtime <= utime() && a->run == true)
	{
		printf("%lu %d died\n", timestamp(a->parameter.starttime),
			early->id + 1);
		a->run = false;
		pthread_mutex_unlock(&a->m_run);
		pthread_mutex_unlock(&early->m_deathtime);
		return ;
	}
	pthread_mutex_unlock(&a->m_run);
	pthread_mutex_unlock(&early->m_deathtime);
}

void	*vitalmonitor(void *data)
{
	t_a				*a;
	t_philo			*early;
	unsigned long	time;

	a = (t_a *)data;
	while (1)
	{
		if (run_check(&a->m_run, &a->run))
			return (NULL);
		early = first_dietime(a);
		pthread_mutex_lock(&early->m_deathtime);
		time = early->deathtime;
		pthread_mutex_unlock(&early->m_deathtime);
		real_usleep(time);
		death_check(a, early);
	}
}
