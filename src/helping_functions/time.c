/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 10:53:27 by pharbst           #+#    #+#             */
/*   Updated: 2023/01/23 02:50:53 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	real_usleep(unsigned long wakeuptime)
{
	unsigned long	now;

	now = utime();
	while (now < wakeuptime)
	{
		now = utime();
		usleep(100);
	}
}

unsigned long	utime(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000000 + tv.tv_usec);
}

unsigned long	timestamp(unsigned long starttime)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (((tv.tv_sec * 1000000 + tv.tv_usec) - starttime) / 1000);
}
