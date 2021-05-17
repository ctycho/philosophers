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

#include "philo_three.h"

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

int				init_args(t_philo *ph, int ac, char **av)
{
	ph->ph_cnt = ft_atoi(av[1]);
	ph->t_to_die = ft_atoi(av[2]);
	ph->t_to_eat = ft_atoi(av[3]);
	ph->t_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		ph->meals_max = ft_atoi(av[5]);
	else
		ph->meals_max = -1;
	if (ph->ph_cnt < 2 || ph->ph_cnt > 200)
		return (-1);
	return (0);
}

int				init_philo(t_philo *ph)
{
	int			i;

	i = -1;
	while (++i < ph->ph_cnt)
	{
		ph[i].id = i + 1;
		ph[i].forks = ph->forks;
		ph[i].write = ph->write;
		ph[i].start_time = get_time();
		ph[i].last_eat = 0;
	}
	return (0);
}

int				init_semaphores(t_philo *ph)
{
	sem_unlink("forks");
	sem_unlink("write");
	sem_unlink("meal");
	ph->forks = sem_open("forks", O_CREAT, 0777, ph->ph_cnt);
	if (ph->forks == SEM_FAILED)
		return (printf("Error: Couldn't init semaphore for forks!\n"));
	ph->write = sem_open("write", O_CREAT, 0777, 1);
	if (ph->write == SEM_FAILED)
		return (printf("Error: Couldn't init semaphore for meals!\n"));
	ph->meal = sem_open("meal", O_CREAT, 0777, 0);
	if (ph->meal == SEM_FAILED)
		return (printf("Error: Couldn't init semaphore for meals!\n"));
	ph->pid = (pid_t *)malloc(sizeof(pid_t) * ph->ph_cnt);
	if (!ph->pid)
		return (printf("Error: Couldn't allocate memory\n"));
	return (0);
}

int				main(int ac, char **av)
{
	t_philo		*ph;

	if (parser(ac, av))
		return (-1);
	ph = (t_philo *)malloc(sizeof(t_philo) * ft_atoi(av[1]));
	if (!ph)
		return (printf("Error: Couldn't allocate memory\n"));
	if (init_args(ph, ac, av) != 0)
		return (printf("Error: Couldn't init arguements\n"));
	if (init_semaphores(ph) != 0)
		return (-1);
	init_philo(ph);
	create_threads(ph);
	sem_unlink("forks");
	sem_unlink("write");
	sem_unlink("meal");
	sem_close(ph->forks);
	sem_close(ph->write);
	sem_close(ph->meal);
	free(ph);
	return (0);
}
