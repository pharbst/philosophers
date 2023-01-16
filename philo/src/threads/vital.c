/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vital.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 11:43:41 by pharbst           #+#    #+#             */
/*   Updated: 2023/01/16 18:13:32 by pharbst          ###   ########.fr       */
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
    printf("start vitalmonitor\n");
    while(1)
    {
        pthread_mutex_lock(&a->m_run);
        if (a->run == false)
        {
            pthread_mutex_unlock(&a->m_run);
            return (NULL);
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
            printf("==%6lu==        philo%d died", timestamp(a->parameter.starttime), early->id);
            a->run = false;
            pthread_mutex_unlock(&a->m_run);
            pthread_mutex_unlock(&early->m_deathtime);
            return (NULL);
        }
    }
    return (NULL);
}
