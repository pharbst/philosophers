/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 02:21:45 by pharbst           #+#    #+#             */
/*   Updated: 2023/01/21 16:36:38 by pharbst          ###   ########.fr       */
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

# define ERROR_1	"Error: Wrong number of arguments\n"
# define ERROR_2	"Error: memory allocation in init_simulation failed\n"
# define ERROR_3	"Error: mutex init in init_simulation failed\n"
# define ERROR_4	"Error: thread creation in exec_sim failed\n"
# define ERROR_5	"Error: thread joining in exec_sim failed\n"

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
	const int		id;
	unsigned long	deathtime;
	int				eat_count;
	bool			*run;
	t_para			*parameter;
	pthread_mutex_t	*m_run;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	m_deathtime;
	pthread_mutex_t	m_eat_count;
	pthread_t		thread;
}	t_philo;

typedef struct s_a
{
	bool			run;
	t_para			parameter;
	t_philo			*philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	m_run;
	pthread_t		thread;
	pthread_t		thread2;
}	t_a;



/*general helper functions*/

/*philo_atoi is for converting input str in a number valid for the project philo*/
long			philo_atoi(char *str);
/*ft_bzero wipe memory with 0*/
void			ft_bzero(void *s, size_t n);
/*ft_calloc allocate memory and wipe it with 0*/
void			*ft_calloc(size_t nelem, size_t elsize);
unsigned long   ft_strlen(const char *s);
/*utime returns the values of gettimeofday together as a unsigned long in usec*/
unsigned long   utime();
/*timestamp returns the diffrenence of starttime and actual time in ms*/
unsigned long   timestamp(unsigned long starttime);
/*real_usleep is not a real sleep function is is a function waiting for the wakeuptime in the format of utime*/
void			real_usleep(unsigned long wakeuptime);



/*general managing functions*/

/*starts the execution of the simulation*/
int				exec_sim(t_a *a);
/*prepares everything to run the simulation*/
int				init_simulation(t_a *a);



/*thread routine functions*/

/*philo is the main function for all philosophers*/
void			*philo_main(void *philo);
/*vitalmonitor monitors the deathtime of all philos and set the run variable to false if a philo dies*/
void			*vitalmonitor(void *a);
/*food_monitor monitors the eat_count of all philos and set the run variable to false if all philos ate enough*/
void			*food_monitor(void *a);



/*thread routine helper functions*/

/*locks the run mutex and prints the log massage if the run variable is true*/
bool			print_log(t_philo *philo, char *str);
/*fork taking function for philo routine*/
bool			take_fork(t_philo *philo);

#endif