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

#include "philo_two.h"

int				ft_atoi(const char *str)
{
	int		flag;
	int		res;

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
		s->ph[i].forks = ph->forks;
		s->ph[i].write = ph->write;
		s->ph[i].start_time = get_time();
		s->ph[i].last_eat = 0;
		s->ph[i].s = s;
	}
	return (0);
}

int				init_sem(t_global *s, t_philo *ph)
{
	sem_unlink("forks");
	sem_unlink("write");
	ph->forks = sem_open("forks", O_CREAT, 0777, s->ph_cnt);
	if (ph->forks == SEM_FAILED)
		return (printf("Error: Couldn't init semaphore for forks!\n"));
	ph->write = sem_open("write", O_CREAT, 0777, 1);
	if (ph->write == SEM_FAILED)
		return (printf("Error: Couldn't init semaphore for meals!\n"));
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
	if (init_sem(&s, s.ph) != 0)
		return (-1);
	init_philo(&s, s.ph);
	create_threads(&s);
	sem_unlink("forks");
	sem_unlink("write");
	sem_close(s.ph->forks);
	sem_close(s.ph->write);
	free(s.ph);
	return (0);
}
