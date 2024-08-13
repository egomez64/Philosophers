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

int	init_data(t_data *data, char **av)
{
	*data = (t_data){0};
	data->n_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		data->max_eat = ft_atoi(av[5]);
	else
		data->max_eat = 0;
	data->count_satiety = 0;
	data->is_dead = false;
	data->start_time = get_current_time();
	return (0);
}

void	init_philo(t_philo *philo, t_data *data)
{
	int		i;
	t_fork	*tmp;

	i = 0;
	while (data->n_philo > i)
	{
		philo[i].data = data;
		philo[i].id_philo = i + 1;
		philo[i].last_eat = 0;
		philo[i].nb_forks = 0;
		philo[i].l_fork = &data->forks[i % data->n_philo];
		if (philo->data->n_philo > 1)
		{
			philo[i].r_fork = &data->forks[(i + 1) % data->n_philo];
			if (philo[i].id_philo == data->n_philo)
			{
				tmp = philo[i].l_fork;
				philo[i].l_fork = philo[i].r_fork;
				philo[i].r_fork = tmp;
			}
		}
		philo->satiety = 0;
		i++;
	}
}

int	init_mutex(t_data *data)
{
	int	check;
	int	i;

	i = 0;
	while (data->n_philo > i)
	{
		check = pthread_mutex_init(&data->forks->fork_mutex, NULL);
		if (check != 1)
			return (-1);
		i++;
	}
	check = pthread_mutex_init(&data->is_dead_mutex, NULL);
	if (check != 1)
		return (-1);
	check = pthread_mutex_init(&data->printf_mutex, NULL);
	if (check != 1)
		return (-1);
	return (0);
}
