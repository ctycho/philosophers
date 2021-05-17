/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctycho <ctycho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 01:09:19 by ctycho            #+#    #+#             */
/*   Updated: 2021/05/11 03:38:59 by ctycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void				*message(t_global *s, t_philo *ph, int flag, long start)
{
	long			t;

	t = get_time() - start;
	pthread_mutex_lock(&ph->write);
	if (s->alive && s->to <= s->ph_cnt)
	{
		if (flag == DIE)
			printf("%ld ph %d died\n", t, ph->id);
		else if (flag == FORK)
			printf("%ld ph %d has taken a fork\n", t, ph->id);
		else if (flag == EAT)
			printf("%ld ph %d is eating\n", t, ph->id);
		else if (flag == SLEEP)
			printf("%ld ph %d is sleeping\n", t, ph->id);
		else if (flag == THINK)
			printf("%ld ph %d is thinking\n", t, ph->id);
		else if (flag == FULL)
			printf("%ld ph %d is full\n", t, ph->id);
	}
	pthread_mutex_unlock(&ph->write);
	return (NULL);
}

long				get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((long)(time.tv_sec * 1000 + time.tv_usec / 1000));
}

void				waiting_time(long time)
{
	long			current;

	current = get_time();
	while ((get_time() - current) < time)
		usleep(1);
}

int					parser(int ac, char **av)
{
	int i;
	int j;

	if (ac != 5 && ac != 6)
		return (printf("Error: Wrong number of arguements!\n"));
	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] < 48 || av[i][j] > 57)
				return (printf("Error: Arguement is not valid!\n"));
			else
				j++;
		}
		i++;
	}
	return (0);
}
