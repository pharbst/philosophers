/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   judge.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 12:04:51 by pharbst           #+#    #+#             */
/*   Updated: 2022/12/09 07:14:24 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_philo *first_dietime(t_a *a)
{
	t_philo			*early;
	unsigned int	i;

	early = a->philo;
	while (&a->philo[i])
		if (a->philo[i].deathtime < early->deathtime)
			early = &a->philo[i];
	return (early);
}

bool    all_alive(t_a *a)
{
	int i;

	i = 0;
	while(i < a->parameter.philo_count)
		if (a->philo[i++].deathtime <= utime())
			return (a->philo[i - 1].alive = false, false);
	return (true);
}

void	vitalmonitor(t_a *a)
{
	t_philo	*early;

	while (1)
	{
		pthread_mutex_lock(&a->m_run);
		if (a->run == false)
		{
			pthread_mutex_unlock(&a->m_run);
			return ;
		}
		pthread_mutex_unlock(&a->m_run);
		early = first_dietime(a);
		pthread_mutex_lock(&early->m_deathtime);
		if (early->deathtime <= utime())
		{
			printf("==%d==	philo%d died", timestamp(a->parameter.starttime), early->id);
			pthread_mutex_lock(&a->m_run);
			a->run = false;
			pthread_mutex_unlock(&a->m_run);
			pthread_mutex_unlock(&early->m_deathtime);
			return ;
		}
		usleep(1);
	}
}

void    judge(t_a *a)
{
	while(all_alive(a) == true && a->run == true)
		usleep(1);
	
}
