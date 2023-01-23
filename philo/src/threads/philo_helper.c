/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 06:06:58 by pharbst           #+#    #+#             */
/*   Updated: 2023/01/23 02:59:17 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

bool	print_log(t_philo *philo, char *str)
{
	pthread_mutex_lock(philo->m_run);
	if (*(philo->run) == false)
	{
		pthread_mutex_unlock(philo->m_run);
		return (true);
	}
	printf("%lu %d %s\n", timestamp(philo->parameter->starttime),
		philo->id + 1, str);
	pthread_mutex_unlock(philo->m_run);
	return (false);
}
