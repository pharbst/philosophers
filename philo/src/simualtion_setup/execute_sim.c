/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_sim.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 07:06:17 by pharbst           #+#    #+#             */
/*   Updated: 2023/01/21 06:47:49 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	copy_parameter(t_a *a, t_philo *philo)
{
	*(int *)&philo->parameter.eat_count = a->parameter.eat_count;
	*(int *)&philo->parameter.philo_count = a->parameter.philo_count;
	*(int *)&philo->parameter.time_to_die = a->parameter.time_to_die;
	*(int *)&philo->parameter.time_to_eat = a->parameter.time_to_eat;
	*(int *)&philo->parameter.time_to_sleep = a->parameter.time_to_sleep;
	*(unsigned long *)&philo->parameter.starttime = a->parameter.starttime;
}

static bool	setup_philos(t_a *a)
{
	int	pnum;

	pnum = a->parameter.philo_count;
	a->philo = ft_calloc(pnum + 1, sizeof(t_philo));
	pnum = 0;
	printf("setup_philos\n");
	while (pnum < a->parameter.philo_count)
	{
		a->philo[pnum].id = pnum;
		a->philo[pnum].m_run = &a->m_run;
		a->philo[pnum].run = &a->run;
		copy_parameter(a, &a->philo[pnum]);
		a->philo[pnum].deathtime = a->parameter.starttime + a->parameter.time_to_die * 1000;
		if (pthread_mutex_init(&a->philo[pnum].m_id, NULL))
			return (true);
		if (pthread_mutex_init(&a->philo[pnum].m_deathtime, NULL))
			return (true);
		a->philo[pnum].right_fork = ft_calloc(1, sizeof(pthread_mutex_t));
		pnum++;
	}
	a->philo[pnum].id = -1;
	return (false);
}

static void	distribute_forks(t_a *a)
{
	int	i;

	printf("distribute_forks\n");
	a->philo[a->parameter.philo_count - 1].left_fork = a->philo[0].right_fork;
	i = 0;
	while (i < a->parameter.philo_count - 1)
	{
		a->philo[i].left_fork = a->philo[i + 1].right_fork;
		i++;
	}
	a->philo[i].left_fork = a->philo[0].right_fork;
}

static bool	create_philos(t_a *a)
{
	t_philo	*data;

	printf("create_philos\n");
	int	i;
	if (setup_philos(a))
		return (true);
	distribute_forks(a);
	i = -1;
	while (++i < a->parameter.philo_count)
	{
		data = &a->philo[i];
		pthread_create(&a->philo[i].thread, NULL, &philo_main, ((void *)data));
	}
	return (false);
}

bool	execute_sim(t_a *a)
{
	struct timeval	tv;
	int				i;

	printf("execute_sim\n");
	a->run = true;
	printf("input values\n");
	printf("Simulation started with %d philosopers %dms needed to eat %dms needed to sleep %dms to die, each philo should eat %d times\n", a->parameter.philo_count, a->parameter.time_to_eat, a->parameter.time_to_sleep, a->parameter.time_to_die, a->parameter.eat_count);
	gettimeofday(&tv, NULL);
	(*(unsigned long *)&a->parameter.starttime) = tv.tv_sec * 1000000 + tv.tv_usec;
	pthread_mutex_lock(&a->m_run);
	if (create_philos(a))
		return (true);
	i = 0;
	pthread_create(&a->thread, NULL, &vitalmonitor, (void *)a);
	pthread_mutex_unlock(&a->m_run);
	while (i < a->parameter.philo_count)
	{
		pthread_join(a->philo[i].thread, NULL);
		i++;
	}
	pthread_join(a->thread, NULL);
	return (false);
}
