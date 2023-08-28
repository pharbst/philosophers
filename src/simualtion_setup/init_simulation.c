/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_simulation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 09:35:59 by pharbst           #+#    #+#             */
/*   Updated: 2023/01/23 02:51:48 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

bool	allocating_space(t_a *a)
{
	a->philo = ft_calloc(sizeof(t_philo), (a->parameter.philo_count));
	if (!a->philo)
		return (true);
	a->forks = ft_calloc(sizeof(pthread_mutex_t), (a->parameter.philo_count));
	if (!a->forks)
		return (true);
	return (false);
}

bool	mutex_init(t_a *a)
{
	int	i;

	i = 0;
	while (i < a->parameter.philo_count)
	{
		if (pthread_mutex_init(&a->forks[i], NULL))
			return (true);
		if (pthread_mutex_init(&a->philo[i].m_deathtime, NULL))
			return (true);
		if (pthread_mutex_init(&a->philo[i].m_eat_count, NULL))
			return (true);
		i++;
	}
	if (pthread_mutex_init(&a->m_run, NULL))
		return (true);
	return (false);
}

void	distribute_forks(t_a *a)
{
	int	i;

	i = 0;
	while (i < a->parameter.philo_count)
	{
		a->philo[i].right_fork = &a->forks[i];
		i++;
	}
	if (i == 1)
		a->philo[0].left_fork = NULL;
	else
	{
		a->philo[a->parameter.philo_count - 1].left_fork
			= a->philo[0].right_fork;
		i = 0;
		while (i < a->parameter.philo_count - 1)
		{
			a->philo[i].left_fork = a->philo[i + 1].right_fork;
			i++;
		}
	}
}

bool	prepare_philo(t_a *a)
{
	int	i;

	i = 0;
	while (i < a->parameter.philo_count)
	{
		*(int *)&a->philo[i].id = i;
		a->philo[i].m_run = &a->m_run;
		a->philo[i].run = &a->run;
		a->philo[i].parameter = &a->parameter;
		i++;
	}
	return (false);
}

int	init_simulation(t_a *a)
{
	if (allocating_space(a))
		return (1);
	if (mutex_init(a))
		return (2);
	prepare_philo(a);
	distribute_forks(a);
	return (0);
}
