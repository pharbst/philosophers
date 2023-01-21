/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 02:26:25 by pharbst           #+#    #+#             */
/*   Updated: 2023/01/21 07:11:59 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	close_sim(t_a *a)
{
	int	i;

	if (a->philo)
		free(a->philo);
	i = 0;
	if (a->forks)
		while (i < a->parameter.philo_count)
		{
			pthread_mutex_destroy(a->philo[i].left_fork);
			pthread_mutex_destroy(&a->philo[i].m_deathtime);
			pthread_mutex_destroy(&a->philo[i].m_id);
			i++;
		}
	pthread_mutex_destroy(&a->m_run);
	if (a->forks)
		free(a->forks);
	return (printf("Simulation ended\n"), free(a));
}

static bool	init_simulation(t_a *a)
{
	int	i;

	a->philo = ft_calloc(sizeof(t_philo), (a->parameter.philo_count + 2));
	if (!a->philo)
		return (true);
	a->forks = ft_calloc(sizeof(pthread_mutex_t), (a->parameter.philo_count));
	if (!a->forks)
		return (true);
	// if (pthread_mutex_init(&a->write, NULL))
	// 	return (true);
	i = 0;
	while (i < a->parameter.philo_count)
		if (pthread_mutex_init(&a->forks[i++], NULL))
			return (true);
	return (false);
}

t_a	*input_handler(int argc, char** argv)
{
	t_a	*a;

	a = ft_calloc(sizeof(t_a), 1);
	(*(int *)&a->parameter.philo_count) = philo_atoi(argv[1]);
	(*(int *)&a->parameter.time_to_die) = philo_atoi(argv[2]);
	(*(int *)&a->parameter.time_to_eat) = philo_atoi(argv[3]);
	(*(int *)&a->parameter.time_to_sleep) = philo_atoi(argv[4]);
	if (argc == 6)
		(*(int *)&a->parameter.eat_count) = philo_atoi(argv[5]);
	else
		(*(int *)&a->parameter.eat_count) = -1;
	if (a->parameter.philo_count < 1 || a->parameter.time_to_die < 1 || a->parameter.time_to_eat < 1 || a->parameter.time_to_sleep < 1 || (argc == 6 && a->parameter.eat_count < 1))
		return (write(1, "Error: invalid input\n", 21), NULL);
	return (a);
}

int main(int argc, char **argv)
{
	t_a		*a;

	if (argc != 5 && argc != 6)
		return (write(2, "Error: Wrong number of arguments\n", 33), 1);
	a = input_handler(argc, argv);
	if (!a)
		return (1);
	if (init_simulation(a))
		return (close_sim(a), write(2, "Error: initialization failed\n", 29), 2);
	if (execute_sim(a))
		return (close_sim(a), printf("philo died\n"), 0);
	return (close_sim(a), 0);
}
