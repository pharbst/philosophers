/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 02:21:45 by pharbst           #+#    #+#             */
/*   Updated: 2023/01/23 02:47:27 by pharbst          ###   ########.fr       */
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

long			philo_atoi(char *str);
void			ft_bzero(void *s, size_t n);
void			*ft_calloc(size_t nelem, size_t elsize);
unsigned long	ft_strlen(const char *s);
unsigned long	utime(void);
unsigned long	timestamp(unsigned long starttime);
void			real_usleep(unsigned long wakeuptime);

/*general managing functions*/

int				exec_sim(t_a *a);
int				init_simulation(t_a *a);

/*thread routine functions*/

void			*philo_main(void *philo);
void			*vitalmonitor(void *a);
void			*food_monitor(void *a);

/*thread routine helper functions*/

bool			print_log(t_philo *philo, char *str);
bool			take_fork(t_philo *philo);

#endif