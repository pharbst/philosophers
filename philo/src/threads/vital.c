/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vital.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peter <peter@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 11:43:41 by pharbst           #+#    #+#             */
/*   Updated: 2023/01/02 21:25:35 by peter            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_philo *first_dietime(t_a *a)
{
	t_philo			*early;
	unsigned int	i;

	early = a->philo;
	while (&a->philo[i])
    {
        pthread_mutex_lock(&a->philo[i].m_deathtime);
		if (a->philo[i].deathtime < early->deathtime)
			early = &a->philo[i];
        pthread_mutex_unlock(&a->philo[i].m_deathtime);
    }
	return (early);
}

void    vitalmonitor(t_a *a)
{
    t_philo         *early;
    unsigned long   time;
    
    while(1)
    {
        pthread_mutex_lock(&a->m_run);
        if (*(a->run) == false)
        {
            pthread_mutex_unlock(&a->m_run);
            return ;
        }
        pthread_mutex_unlock(&a->m_run);
        early = first_dietime(a);
        pthread_mutex_lock(&early->m_deathtime);
        time = early->deathtime;
        pthread_mutex_unlock(&early->m_deathtime);
        real_usleep(time);
        pthread_mutex_lock(&early->m_deathtime);
        pthread_mutex_lock(&a->m_run);
        if (early->deathtime <= utime() && *(a->run) == true)
        {
            printf("==%d==	philo%d died", timestamp(a->parameter.starttime), early->id);
            *(a->run) = false;
            pthread_mutex_unlock(&a->m_run);
            pthread_mutex_unlock(&early->m_deathtime);
            return ;
        }
    }
}
