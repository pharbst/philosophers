/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 02:21:45 by pharbst           #+#    #+#             */
/*   Updated: 2023/01/21 06:18:42 by pharbst          ###   ########.fr       */
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
	pthread_mutex_t	*m_run;
	bool			*run;
	pthread_mutex_t	m_id;
	int				id;
	// const int		id;
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
	bool			run;
	pthread_mutex_t	m_run;
	t_para			parameter;
	pthread_mutex_t	*forks;
	t_philo			*philo;
	pthread_t		thread;
}	t_a;



/*general helper functions*/

/*philo_atoi is for converting input str in a number valid for the project philo*/
long			philo_atoi(char *str);
/*ft_bzero wipe memory with 0*/
void			ft_bzero(void *s, size_t n);
/*ft_calloc allocate memory and wipe it with 0*/
void			*ft_calloc(size_t nelem, size_t elsize);
/*utime returns the values of gettimeofday together as a unsigned long in usec*/
unsigned long   utime();
/*timestamp returns the diffrenence of starttime and actual time in ms*/
unsigned long   timestamp(unsigned long starttime);
/*real_usleep is not a real sleep function is is a function waiting for the wakeuptime in the format of utime*/
void			real_usleep(unsigned long wakeuptime);



/*general managing functions*/

/*execute_sim starts the execution of the simulation*/
bool			execute_sim(t_a *a);



/*thread routine functions*/

/*philo is the main function for all philosophers*/
void			*philo_main(void *philo);
/*vitalmonitor monitors the deathtime of all philos and set the run variable to false if a philo dies*/
void			*vitalmonitor(void *a);



// /*thread routine helper functions*/

// /*locks the run mutex and prints the log massage if the run variable is true*/
// bool			print_log(t_philo *philo, char *str);
// /*fork taking function for philo routine*/
// bool			take_fork(t_philo *philo);

#endif