/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 02:26:25 by pharbst           #+#    #+#             */
/*   Updated: 2022/12/05 07:37:10 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	close_sim(t_a *a)
{
	printf("Simulation ended\n");
	return (free(a));
}

t_a	*input_handler(int argc, char** argv)
{
	t_a	*a;

	a = malloc(sizeof(t_a));
	(*(int *)&a->philo_count) = philo_atoi(argv[1]);
	(*(int *)&a->time_to_die) = philo_atoi(argv[2]);
	(*(int *)&a->time_to_eat) = philo_atoi(argv[3]);
	(*(int *)&a->time_to_sleep) = philo_atoi(argv[4]);
	if (argc == 6)
		a->eat_count = philo_atoi(argv[5]);
	else
		a->eat_count = -1;
	if (a->philo_count < 1 || a->time_to_die < 1 || a->time_to_eat < 1 || a->time_to_sleep < 1 || (argc == 6 && a->eat_count < 1))
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
	if (execute_sim(a))
		return (close_sim(a), printf("philo died\n"), 1);
	return (close_sim(a), 0);
}
