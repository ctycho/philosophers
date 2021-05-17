/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctycho <ctycho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 01:01:15 by ctycho            #+#    #+#             */
/*   Updated: 2021/05/11 03:49:33 by ctycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H

# include <stdio.h>
# include <unistd.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <semaphore.h>
# include <signal.h>

# define DIE 1
# define FORK 2
# define EAT 3
# define SLEEP 4
# define THINK 5
# define FULL 6

typedef struct		s_philo
{
	pthread_t		th;
	pid_t			*pid;
	sem_t			*write;
	sem_t			*forks;
	sem_t			*meal;
	int				id;
	long			start_time;
	long			last_eat;
	int				ph_cnt;
	long			t_to_die;
	long			t_to_eat;
	long			t_to_sleep;
	int				meals_max;
}					t_philo;

int					output(char *str);
void				*message(t_philo *ph, int flag, long start);
int					parser(int ac, char **av);
long				get_time(void);
int					create_threads(t_philo *ph);
void				*life_path(void *par);
void				waiting_time(long time);

#endif
