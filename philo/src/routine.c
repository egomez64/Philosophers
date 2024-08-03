/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 17:42:50 by egomez            #+#    #+#             */
/*   Updated: 2024/08/02 17:42:53 by egomez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	check_death(t_philo *philo)
{
	size_t	time;
	int		i;

	pthread_mutex_lock(&philo->data->is_dead_mutex);
	if (philo->data->is_dead)
	{
		pthread_mutex_unlock(&philo->data->is_dead_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->is_dead_mutex);
	time = get_current_time();
	i= 0;
	while (philo->data->n_philo > i)
	{
		if (time - philo[i].last_eat >= (unsigned long)philo->data->time_to_die)
		{
			pthread_mutex_lock(&philo->data->is_dead_mutex);
			philo->data->is_dead = true;
			pthread_mutex_unlock(&philo->data->is_dead_mutex);
			printf("%zu %d died\n", time, philo[i].id_philo);
		}
		i++;
	}
	return (0);
}

void	philo_think(t_philo *philo)
{
	printf("%zu %d is thinking\n", get_current_time(), philo->id_philo);
}

void	philo_sleep(t_philo *philo)
{
	printf("%zu %d is sleeping\n", get_current_time(), philo->id_philo);
	ft_usleep(philo->data->time_to_sleep);
}

void	philo_eat(t_philo *philo)
{
	size_t	time;

	pthread_mutex_lock(&philo->l_fork->fork_mutex);
	pthread_mutex_lock(&philo->r_fork->fork_mutex);
	time = get_current_time();
	printf("%zu %d is eating\n", time, philo->id_philo);
	philo->last_eat = time;
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(&philo->r_fork->fork_mutex);
	pthread_mutex_unlock(&philo->l_fork->fork_mutex);
}

void	*routine(t_philo *philo)
{
	if (philo->id_philo % 2)
		ft_usleep(50);
	while (1)
	{
		if (check_death(philo)
			|| (philo->data->max_eat
				&& (philo->data->satiety >= philo->data->max_eat)))
			return (NULL);
		wait_for_forks(philo);
		if (check_death(philo)
			|| (philo->data->max_eat
				&& (philo->data->satiety >= philo->data->max_eat)))
			return (NULL);
		philo_eat(philo);
		if (check_death(philo)
			|| (philo->data->max_eat
				&& (philo->data->satiety >= philo->data->max_eat)))
			return (NULL);
		philo_sleep(philo);
	}
	return (NULL);
}
