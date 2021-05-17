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

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <stdio.h>
# include <unistd.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>

# define DIE 1
# define FORK 2
# define EAT 3
# define SLEEP 4
# define THINK 5
# define FULL 6

typedef struct		s_philo
{
	void 			*s;
	pthread_t		th;
	pthread_mutex_t	write;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	int				id;
	long			start_time;
	long			last_eat;
}					t_philo;

typedef struct		s_global
{
	t_philo 		*ph;
	int				alive;
	int 			ph_cnt;
	long			t_to_die;
	long			t_to_eat;
	long			t_to_sleep;
	int				meals_max;
	int 			to;
}					t_global;

int					output(char *str);
void				*message(t_global *s, t_philo *ph, int flag, long start);
int					parser(int ac, char **av);
long				get_time(void);
int					create_threads(t_global *s);
void				*life_path(void *par);
void				waiting_time(long time);
int					full(t_philo *ph);

#endif
