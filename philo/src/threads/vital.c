/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vital.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 11:43:41 by pharbst           #+#    #+#             */
/*   Updated: 2023/01/21 07:08:50 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_philo *first_dietime(t_a *a)
{
	t_philo			*early;
	unsigned int	i;

	early = a->philo;
    i = 0;
	while (a->philo[i].id != -1)
    {
        pthread_mutex_lock(&a->philo[i].m_deathtime);
		if (a->philo[i].deathtime < early->deathtime)
			early = &a->philo[i];
        pthread_mutex_unlock(&a->philo[i].m_deathtime);
        i++;
    }
	return (early);
}

void    *vitalmonitor(void *data)
{
    t_philo         *early;
    t_a             *a;
    unsigned long   time;
    
    a = (t_a *)data;
    printf("==%6lu==		start vitalmonitor\n", timestamp(a->parameter.starttime));
    while(1)
    {
        pthread_mutex_lock(&a->m_run);
        if (a->run == false)
        {
            pthread_mutex_unlock(&a->m_run);
            return (printf("%lu vitalmonitor is returning\n", timestamp(a->parameter.starttime)), NULL);
        }
        pthread_mutex_unlock(&a->m_run);
        early = first_dietime(a);
        pthread_mutex_lock(&early->m_deathtime);
        time = early->deathtime;
        pthread_mutex_unlock(&early->m_deathtime);
        real_usleep(time);
        pthread_mutex_lock(&early->m_deathtime);
        pthread_mutex_lock(&a->m_run);
        if (early->deathtime <= utime() && a->run == true)
        {
            printf("%lu %d died\n", timestamp(a->parameter.starttime), early->id);
            a->run = false;
            pthread_mutex_unlock(&a->m_run);
            pthread_mutex_unlock(&early->m_deathtime);
            return (printf("%lu vitalmonitor is returning\n", timestamp(a->parameter.starttime)), NULL);
        }
        pthread_mutex_unlock(&a->m_run);
        pthread_mutex_unlock(&early->m_deathtime);
    }
    return (printf("%lu vitalmonitor is returning\n", timestamp(a->parameter.starttime)), NULL);
}
