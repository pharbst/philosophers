/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 02:26:25 by pharbst           #+#    #+#             */
/*   Updated: 2022/12/05 03:52:52 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_a	input_handler(int argc char** argv)
{
	t_a	a;

	a.philo_count = philo_atoi(argv[1]);
	a.time_to_die = philo_atoi(argv[2]);
	a.time_to_eat = philo_atoi(argv[3]);
	a.time_to_sleep = philo_atoi(argv[4]);
	if (argc == 6)
		a.eat_count = philo_atoi(argv[5]);
	else
		a.eat_count = -1;
	if (!a.philo_count || !a.time_to_die || !a.time_to_eat || !a.time_to_sleep || !a.eat_count)
		return (printf("Error: invalid input"), NULL);
	return (a);
}

int main(int argc, char **argv)
{
	t_a		a;

	if (argc != 5 && argc != 6)
		return (printf("Error: Wrong number of arguments"), 1);
	a = input_handler(argc, argv);
	if (!a)
		return (1);
	
}
