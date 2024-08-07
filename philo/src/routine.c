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

int	dead_state;

int	check_death(t_philo *philo)
{
	size_t	time;

	pthread_mutex_lock(&philo->data->is_dead_mutex);
	if (philo->data->is_dead)
	{
		pthread_mutex_unlock(&philo->data->is_dead_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->is_dead_mutex);
	time = get_current_time() - philo->data->start_time;
	if (time - philo->last_eat >= (unsigned long)philo->data->time_to_die)
	{
		pthread_mutex_lock(&philo->data->is_dead_mutex);
		philo->data->is_dead = true;
		pthread_mutex_unlock(&philo->data->is_dead_mutex);
		pthread_mutex_lock(&philo->data->printf_mutex);
		if (!dead_state)
			printf("%zu %d died\n", time, philo->id_philo);
		dead_state = 1;
		pthread_mutex_unlock(&philo->data->printf_mutex);
	}
	return (0);
}

void	philo_think(t_philo *philo)
{
	size_t	time;

	if (philo->data->is_dead)
		return ;
	time = get_current_time() - philo->data->start_time;
	pthread_mutex_lock(&philo->data->printf_mutex);
	printf("%zu %d is thinking\n", time, philo->id_philo);
	pthread_mutex_unlock(&philo->data->printf_mutex);
}

void	philo_sleep(t_philo *philo)
{
	size_t	time;

	if (philo->data->is_dead)
		return ;
	time = get_current_time() - philo->data->start_time;
	pthread_mutex_lock(&philo->data->printf_mutex);
	if (philo->data->is_dead)
	{
		pthread_mutex_unlock(&philo->data->printf_mutex);
		return ;
	}
	printf("%zu %d is sleeping\n", time, philo->id_philo);
	pthread_mutex_unlock(&philo->data->printf_mutex);
	pthread_mutex_lock(&philo->data->time_to_sleep_mutex);
	ft_usleep(philo->data->time_to_eat, philo);
	pthread_mutex_unlock(&philo->data->time_to_sleep_mutex);
}

void	philo_eat(t_philo *philo)
{
	size_t	time;

	if (philo->data->is_dead)
		return ;
	time = get_current_time() - philo->data->start_time;
	pthread_mutex_lock(&philo->data->printf_mutex);
	if (check_death(philo))
	{
		pthread_mutex_unlock(&philo->data->printf_mutex);
		return ;
	}
	if (philo->data->is_dead)
	{
		pthread_mutex_unlock(&philo->data->printf_mutex);
		return ;
	}
	printf("%zu %d is eating\n", time, philo->id_philo);
	pthread_mutex_unlock(&philo->data->printf_mutex);
	pthread_mutex_lock(&philo->data->time_to_sleep_mutex);
	ft_usleep(philo->data->time_to_eat, philo);
	pthread_mutex_unlock(&philo->data->time_to_sleep_mutex);
	philo->last_eat = time;
	philo->satiety ++;
	pthread_mutex_lock(&philo->l_fork->fork_mutex);
	pthread_mutex_lock(&philo->r_fork->fork_mutex);
	philo->l_fork->usable = 0;
	philo->r_fork->usable = 0;
	pthread_mutex_unlock(&philo->r_fork->fork_mutex);
	pthread_mutex_unlock(&philo->l_fork->fork_mutex);
	philo->nb_forks = 0;
}

void	*routine(t_philo *philo)
{
	dead_state = 0;
	if (philo->id_philo % 2)
		ft_usleep(50, philo);
	while (1)
	{
		if (check_death(philo))
			return (NULL);
		philo_think(philo);
		if (check_death(philo))
			return (NULL);
		wait_for_forks(philo);
		if (check_death(philo))
			return (NULL);
		philo_eat(philo);
		if (check_death(philo))
			return (NULL);
		if (philo->data->max_eat > 0 && check_satiety(philo))
			return (NULL);
		philo_sleep(philo);
	}
}
