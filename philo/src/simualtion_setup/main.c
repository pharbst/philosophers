/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 02:26:25 by pharbst           #+#    #+#             */
/*   Updated: 2023/01/23 02:21:08 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	close_sim(t_a *a, int error_code)
{
	int	i;

	if (error_code)
	{
		i = 0;
		if (a->forks)
			while (i < a->parameter.philo_count)
			{
				pthread_mutex_destroy(a->philo[i].left_fork);
				pthread_mutex_destroy(&a->philo[i].m_deathtime);
				pthread_mutex_destroy(&a->philo[i].m_eat_count);
				i++;
			}
		if (a->philo)
			free(a->philo);
		pthread_mutex_destroy(&a->m_run);
		if (a->forks)
			free(a->forks);
	}
	return (free(a));
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
	int		error_code;

	if (argc != 5 && argc != 6)
		return (write(2, ERROR_1, ft_strlen(ERROR_1)), 1);
	a = input_handler(argc, argv);
	if (!a)
		return (1);
	error_code = init_simulation(a);
	if (error_code == 0)
	{
		error_code = exec_sim(a);
		if (error_code == 0)
			return (close_sim(a, 3), 0);
		else if (error_code == 1)
			return (close_sim(a, 2), write(2, ERROR_4, ft_strlen(ERROR_4)), 4);
		else if (error_code == 2)
			return (close_sim(a, 2), write(2, ERROR_5, ft_strlen(ERROR_5)), 5);
	}
	else if (error_code == 1)
		return (close_sim(a, 2), write(2, ERROR_2, ft_strlen(ERROR_2)), 2);
	else if (error_code == 2)
		return (close_sim(a, 2), write(2, ERROR_3, ft_strlen(ERROR_3)), 3);
}
