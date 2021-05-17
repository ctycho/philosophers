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

#include "philo_two.h"

int				dead_loop_2(t_global *s, t_philo *ph, int i)
{
	long		time;

	while (i < s->ph_cnt)
	{
		time = get_time() - ph[i].start_time - ph[i].last_eat;
		if (time > s->t_to_die)
		{
			message(s, ph, DIE, ph->start_time);
			s->alive = 0;
			return (1);
		}
		else if (s->meals_max != -1 && s->to >= s->ph_cnt)
		{
			usleep(10);
			printf("Everyone is full\n");
			return (1);
		}
		i++;
	}
	return (0);
}

void			*dead_loop(void *par)
{
	t_global	*s;
	t_philo		*ph;
	int			i;

	ph = (t_philo *)par;
	s = (t_global *)ph->s;
	ph = s->ph;
	while (1)
	{
		i = 0;
		if (dead_loop_2(s, ph, i) == 1)
			return (NULL);
	}
}

int				eating(t_global *s, t_philo *ph)
{
	sem_wait(ph->forks);
	sem_wait(ph->forks);
	message(s, ph, FORK, ph->start_time);
	ph->last_eat = get_time() - ph->start_time;
	message(s, ph, EAT, ph->start_time);
	waiting_time(s->t_to_eat);
	sem_post(ph->forks);
	sem_post(ph->forks);
	return (0);
}

void			*life_path(void *par)
{
	t_global	*s;
	t_philo		*ph;
	int			i;

	ph = (t_philo *)par;
	s = (t_global *)ph->s;
	i = 0;
	if (ph->id % 2 == 0)
		waiting_time(s->t_to_eat);
	while (s->alive)
	{
		eating(s, ph);
		i++;
		if (s->meals_max != -1 && i >= s->meals_max)
		{
			s->to++;
			message(s, ph, FULL, ph->start_time);
			return (NULL);
		}
		message(s, ph, SLEEP, ph->start_time);
		waiting_time(s->t_to_sleep);
		message(s, ph, THINK, ph->start_time);
	}
	return (NULL);
}

int				create_threads(t_global *s)
{
	int			i;
	pthread_t	died;

	i = -1;
	while (++i < s->ph_cnt)
	{
		if (pthread_create(&s->ph[i].th, NULL, life_path, \
		(void *)&s->ph[i]) != 0)
			return (printf("Error: Couldn't create a thread!\n"));
	}
	if (pthread_create(&died, NULL, dead_loop, (void *)&s) != 0)
		return (printf("Error: Couldn't create a thread!\n"));
	i = -1;
	if (pthread_join(died, NULL) != 0)
		return (printf("Error: Couldn't wait a thread!\n"));
	while (++i < s->ph_cnt)
		if (pthread_join(s->ph[i].th, NULL) != 0)
			return (printf("Error: Couldn't wait a thread!\n"));
	return (0);
}
