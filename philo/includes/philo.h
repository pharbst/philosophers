/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 02:21:45 by pharbst           #+#    #+#             */
/*   Updated: 2022/12/05 07:13:52 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>
# include <stdbool.h>

typedef struct s_philo
{
	bool			alive;
	int				id;
	int				eat_count;
	int				last_eat;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}	t_philo;

typedef struct s_a
{
	int				philo_count;
	const int		time_to_die;
	const int		time_to_eat;
	const int		time_to_sleep;
	int				eat_count;
	int				start_time;
	int				dead;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write;
	pthread_mutex_t	dead_mutex;
	t_philo			*philo;
}	t_a;

long		philo_atoi(char *str);
bool		execute_sim(t_a *a);

#endif