/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 15:51:29 by egomez            #+#    #+#             */
/*   Updated: 2024/08/01 15:51:31 by egomez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void    init_data(t_data *data, char **av)
{
	struct timeval	time;
	(*data).n_philo = ft_atoi(av[1]);
	(*data).time_to_die = ft_atoi(av[2]);
	(*data).time_to_eat = ft_atoi(av[3]);
	(*data).time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		(*data).max_eat = ft_atoi(av[5]);
	else
		(*data).max_eat = NULL;
	if (gettimeofday(&time, NULL))
		return ;
	(*data).start_time = time.tv_usec;
	(*data).nb_of_eat = 0;
}

void	init_philo(t_philo *philo, t_data data)
{
	int	i;

	i = 0;
	while (data.n_philo > i)
	{
		philo[i].id_philo = i + 1;
		philo[i].is_dead = false;
		philo[i].last_eat = 0;
		philo[i].l_fork->id_fork = i;
		if (i = data.n_philo)
			philo[i].r_fork = philo[0].l_fork->id_fork;
		else
			philo[i].r_fork->id_fork = i + 1;
		i++;
	}
}
