/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctycho <ctycho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 00:07:29 by ctycho            #+#    #+#             */
/*   Updated: 2021/05/11 03:52:05 by ctycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void			*dead_loop(void *par)
{
	t_philo		*ph;
	long		time;
	int			i;

	ph = (t_philo *)par;
	i = -1;
	while (1)
	{
		time = get_time() - ph->start_time - ph->last_eat;
		if (time > ph->t_to_die)
		{
			message(ph, DIE, ph->start_time);
			while (++i < ph->ph_cnt)
				sem_post(ph->meal);
			exit(1);
		}
	}
}

int				eating(t_philo *ph)
{
	sem_wait(ph->forks);
	sem_wait(ph->forks);
	message(ph, FORK, ph->start_time);
	message(ph, FORK, ph->start_time);
	ph->last_eat = get_time() - ph->start_time;
	message(ph, EAT, ph->start_time);
	waiting_time(ph->t_to_eat);
	sem_post(ph->forks);
	sem_post(ph->forks);
	return (0);
}

int				child_procces(t_philo *ph, int i)
{
	int			count;

	ph->id = i + 1;
	ph->start_time = get_time();
	if (pthread_create(&ph->th, NULL, dead_loop, (void *)ph) != 0)
		return (printf("Error: Couldn't create a thread!\n"));
	count = 0;
	while (1)
	{
		eating(ph);
		count++;
		if (ph->meals_max != -1 && count >= ph->meals_max)
		{
			message(ph, FULL, ph->start_time);
			sem_post(ph->meal);
			exit (1);
		}
		message(ph, SLEEP, ph->start_time);
		waiting_time(ph->t_to_sleep);
		message(ph, THINK, ph->start_time);
	}
}

int				create_threads(t_philo *ph)
{
	int			i;

	i = -1;
	while (++i < ph->ph_cnt)
	{
		ph->pid[i] = fork();
		if (ph->pid[i] == 0)
			child_procces(ph, i);
	}
	i = -1;
	if (ph->meals_max != -1)
		while (++i < ph->ph_cnt)
			sem_wait(ph->meal);
	waitpid(-1, NULL, 0);
	i = -1;
	while (++i < ph->ph_cnt)
		kill(ph->pid[i], SIGTERM);
	return (0);
}
