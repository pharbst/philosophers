/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 13:22:18 by pharbst           #+#    #+#             */
/*   Updated: 2023/01/23 13:25:23 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

bool	run_check(pthread_mutex_t *m_run, bool *run)
{
	pthread_mutex_lock(m_run);
	if (*run == false)
	{
		pthread_mutex_unlock(m_run);
		return (true);
	}
	pthread_mutex_unlock(m_run);
	return (false);
}

// {
// 	pthread_mutex_lock(&a->m_run);
// 	if (a->run == false)
// 	{
// 		pthread_mutex_unlock(&a->m_run);
// 		return (true);
// 	}
// 	pthread_mutex_unlock(&a->m_run);
// 	return (false);
// }
