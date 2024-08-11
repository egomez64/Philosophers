/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 14:25:45 by egomez            #+#    #+#             */
/*   Updated: 2024/08/11 14:25:46 by egomez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	check_death(t_philo *philo)
{
	int		i;
	size_t	time;

	i = 0;
	while (philo->data->n_philo > i)
	{
		time = get_current_time() - philo->data->start_time;
		pthread_mutex_lock(&philo->data->is_dead_mutex);
		if (time - philo[i].last_eat >= (size_t)philo->data->time_to_die)
		{
			if (philo->data->is_dead)
			{
				pthread_mutex_unlock(&philo->data->is_dead_mutex);
				return (1);
			}
			pthread_mutex_lock(&philo->data->printf_mutex);
			printf("%zu %d died\n", time, philo[i].id_philo);
			pthread_mutex_unlock(&philo->data->printf_mutex);
			philo->data->is_dead = true;
		}
		if (philo->data->is_dead)
		{
			pthread_mutex_unlock(&philo->data->is_dead_mutex);
			return (1);
		}
		i++;
		pthread_mutex_unlock(&philo->data->is_dead_mutex);
		usleep(100);
	}
	return (0);
}

int	check_satiety(t_philo *philo)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&philo->data->is_dead_mutex);
	while (philo->data->n_philo > i)
	{
		if (philo->data->max_eat > 0 && philo[i].satiety >= philo->data->max_eat)
			philo->data->count_satiety++;
		i++;
	}
	if (philo->data->count_satiety == philo->data->n_philo)
	{
		philo->data->is_dead = true;
		pthread_mutex_unlock(&philo->data->is_dead_mutex);
		return (1);
	}
	philo->data->count_satiety = 0;
	pthread_mutex_unlock(&philo->data->is_dead_mutex);
	return (0);
}

void	supervisor(t_philo	*philo)
{
	size_t	time;

	if (philo->data->n_philo > 1)
	{
		while (!check_death(philo))
			check_satiety(philo);
	}
	else
	{
		time = get_current_time() - philo->data->start_time;
		while (time  < (size_t)philo->data->time_to_die)
			time = get_current_time() - philo->data->start_time;
		pthread_mutex_lock(&philo->data->is_dead_mutex);
		philo->data->is_dead = true;
		pthread_mutex_unlock(&philo->data->is_dead_mutex);
		printf("%zu 1 died\n", time);
	}
}
