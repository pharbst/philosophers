/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 01:24:42 by pharbst           #+#    #+#             */
/*   Updated: 2023/01/20 02:27:27 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static bool	print_log(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->m_run);
	if (*(philo->run) == false)
		return (true);
	printf("%lu %d %s", timestamp(philo->parameter.starttime), philo->id, str);
	pthread_mutex_unlock(&philo->m_run);
	return (false);
}

static bool philo_init_thinking(t_philo *philo)
{
	if (print_log(philo, "is thinking"))
		return (true);
	return (false);
}

static bool	take_fork(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		print_log(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_log(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		print_log(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print_log(philo, "has taken a fork");
	}
}

void	*philo_main(void *data)
{
	t_philo	*philo;

	philo = data;
	if (philo_init_thinking(philo))
		return (NULL);
	while (1)
	{
		if (take_fork(philo))
			return (NULL);
		if (philo_eat(philo))
			return (NULL);
		if (philo_sleep(philo))
			return (NULL);
		if (philo_think(philo))
			return (NULL);
	}
}
