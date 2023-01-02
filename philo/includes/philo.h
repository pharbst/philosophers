/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peter <peter@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 02:21:45 by pharbst           #+#    #+#             */
/*   Updated: 2023/01/02 23:21:31 by peter            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include <stdint.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>
# include <stdbool.h>

typedef struct s_para
{
	const int			philo_count;
	const int			time_to_die;
	const int			time_to_eat;
	const int			time_to_sleep;
	const int			eat_count;
	const unsigned long	starttime;
}	t_para;


typedef struct s_philo
{
	pthread_mutex_t	m_alive;
	bool			alive;
	pthread_mutex_t	*m_run;
	bool			*run;
	int				id;
	int				eat_count;
	pthread_mutex_t	m_deathtime;
	unsigned long	deathtime;
	t_para			parameter;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}	t_philo;

typedef struct s_a
{
	bool			*run;
	pthread_mutex_t	*m_run;
	t_para			parameter;
	pthread_mutex_t	*forks;
	t_philo			*philo;
}	t_a;

/*philo_atoi is for converting input str in a number valid for the project philo*/
long			philo_atoi(char *str);
/*execute_sim starts the execution of the simulation*/
bool			execute_sim(t_a *a);
/*ft_calloc allocate memory and wipe it with 0*/
void			*ft_calloc(size_t nelem, size_t elsize);
/*ft_bzero wipe memory with 0*/
void	ft_bzero(void *s, size_t n);
/*philo is the main function for all philosophers*/
void			philo(t_philo philo);
/*utime returns the values of gettimeofday together as a unsigned long in usec*/
unsigned long   utime();
/*timestamp returns the diffrenence of starttime and actual time in ms*/
unsigned long   timestamp(unsigned long starttime);
/*real_usleep is not a real sleep function is is a function waiting for the wakeuptime in the format of utime*/
void    real_usleep(unsigned long wakeuptime);


#endif