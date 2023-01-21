/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_take_fork.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 06:01:42 by pharbst           #+#    #+#             */
/*   Updated: 2023/01/21 07:02:26 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static bool	fork_even(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	if (print_log(philo, "has taken a fork"))
	{
		pthread_mutex_unlock(philo->right_fork);
		return (true);
	}
	pthread_mutex_lock(philo->left_fork);
	if (print_log(philo, "has taken a fork"))
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return (true);
	}
	return (false);
}

static bool	fork_odd(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	if (print_log(philo, "has taken a fork"))
	{
		pthread_mutex_unlock(philo->left_fork);
		return (true);
	}
	pthread_mutex_lock(philo->right_fork);
	if (print_log(philo, "has taken a fork"))
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (true);
	}
	return (false);
}

bool	take_fork(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		if (fork_even(philo))
			return (true);
	}
	else
	{
		if (fork_odd(philo))
			return (true);
	}
	return (false);
}
