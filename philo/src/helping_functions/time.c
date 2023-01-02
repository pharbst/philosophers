/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peter <peter@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 10:53:27 by pharbst           #+#    #+#             */
/*   Updated: 2023/01/03 00:24:15 by peter            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void    real_usleep(unsigned long wakeuptime)
{
    unsigned long   now;

    now = utime();
    while (now < wakeuptime)
        now = utime();
}

unsigned long   utime()
{
    struct timeval  tv;

    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000000 + tv.tv_usec);
}

unsigned long   timestamp(unsigned long starttime)
{
    struct timeval  tv;

    gettimeofday(&tv, NULL);
    return (((tv.tv_sec * 1000000 + tv.tv_usec) - starttime) / 1000);
}
