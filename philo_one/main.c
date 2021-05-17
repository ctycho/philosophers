/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctycho <ctycho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 01:00:07 by ctycho            #+#    #+#             */
/*   Updated: 2021/05/11 03:51:22 by ctycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int				ft_atoi(const char *str)
{
	int			flag;
	int			res;

	flag = 1;
	res = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if ((*str == '-') || (*str == '+'))
		if (*str++ == '-')
			flag = -flag;
	while (*str >= '0' && *str <= '9')
		res = (res * 10) + (*str++ - 48);
	return (res * flag);
}

int				init_args(t_global *s, int ac, char **av)
{
	s->ph_cnt = ft_atoi(av[1]);
	s->t_to_die = ft_atoi(av[2]);
	s->t_to_eat = ft_atoi(av[3]);
	s->t_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		s->meals_max = ft_atoi(av[5]);
	else
		s->meals_max = -1;
	if (s->ph_cnt < 2 || s->ph_cnt > 200)
		return (-1);
	s->alive = 1;
	return (0);
}

int				init_philo(t_global *s, t_philo *ph)
{
	int			i;

	i = -1;
	s->alive = 1;
	s->to = 0;
	while (++i < s->ph_cnt)
	{
		s->ph[i].id = i + 1;
		s->ph[i].left_fork = &ph->forks[i];
		s->ph[i].right_fork = &ph->forks[(i + 1) % s->ph_cnt];
		s->ph[i].last_eat = 0;
		s->ph[i].s = s;
	}
	return (0);
}

int				init_mutex(t_global *s, t_philo *ph)
{
	int			i;

	i = -1;
	ph->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) \
		* s->ph_cnt);
	if (!ph->forks)
		return (printf("can't allocate memory for forks array!\n"));
	while (++i < s->ph_cnt)
	{
		if (pthread_mutex_init(&ph->forks[i], NULL) != 0)
			return (printf("Error: Couldn't init mutex(forks)!\n"));
	}
	if (pthread_mutex_init(&ph->write, NULL) != 0)
		return (printf("Error: Couldn't init mutex(write)!\n"));
	return (0);
}

int				main(int ac, char **av)
{
	t_global	s;

	if (parser(ac, av))
		return (-1);
	s.ph = (t_philo *)malloc(sizeof(t_philo) * ft_atoi(av[1]));
	if (!s.ph)
		return (printf("Error: Couldn't allocate memory\n"));
	if (init_args(&s, ac, av) != 0)
		return (printf("Error: Couldn't init arguements\n"));
	if (init_mutex(&s, s.ph) != 0)
		return (-1);
	init_philo(&s, s.ph);
	create_threads(&s);
	free(s.ph);
	return (0);
}
