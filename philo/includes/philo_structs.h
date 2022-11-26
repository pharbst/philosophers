/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_struct.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 07:47:44 by pharbst           #+#    #+#             */
/*   Updated: 2022/11/26 07:48:57 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_STRUCT_H
# define PHILO_STRUCT_H

# include "philo.h"

typedef struct s_input
{
	const int	philo_count;
	const int	time_to_die;
	const int	time_to_eat;
	const int	time_to_sleep;
	const int	must_eat;
}	t_input;

#endif