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

int	interrupt(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->is_dead_mutex);
	if (philo->data->is_dead)
	{
		pthread_mutex_unlock(&philo->data->is_dead_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->is_dead_mutex);
	return (0);
}

static void	philo_think(t_philo *philo)
{
	if (interrupt(philo))
		return ;
	pthread_mutex_lock(&philo->data->printf_mutex);
	print(philo, "is thinking");
	pthread_mutex_unlock(&philo->data->printf_mutex);
}

static void	philo_sleep(t_philo *philo)
{
	if (interrupt(philo))
		return ;
	pthread_mutex_lock(&philo->data->printf_mutex);
	print(philo, "is sleeping");
	pthread_mutex_unlock(&philo->data->printf_mutex);
	ft_usleep(philo->data->time_to_sleep, philo);
}

static void	philo_eat(t_philo *philo)
{
	if (interrupt(philo))
		return ;
	pthread_mutex_lock(&philo->data->printf_mutex);
	print(philo, "is eating");
	pthread_mutex_unlock(&philo->data->printf_mutex);
	pthread_mutex_lock(&philo->data->is_dead_mutex);
	philo->last_eat = get_current_time() - philo->data->start_time;
	pthread_mutex_unlock(&philo->data->is_dead_mutex);
	ft_usleep(philo->data->time_to_eat, philo);
	pthread_mutex_lock(&philo->l_fork->fork_mutex);
	pthread_mutex_lock(&philo->r_fork->fork_mutex);
	philo->l_fork->usable = 0;
	philo->r_fork->usable = 0;
	pthread_mutex_unlock(&philo->r_fork->fork_mutex);
	pthread_mutex_unlock(&philo->l_fork->fork_mutex);
	pthread_mutex_lock(&philo->data->is_dead_mutex);
	philo->satiety++;
	philo->nb_forks = 0;
	pthread_mutex_unlock(&philo->data->is_dead_mutex);
}

void	*routine(t_philo *philo)
{
	if (philo->id_philo % 2 == 0)
	{
		philo_think(philo);
		usleep(50);
	}
	while (1)
	{
		if (interrupt(philo))
			return (NULL);
		wait_for_forks(philo);
		if (interrupt(philo) || philo->data->n_philo == 1)
			return (NULL);
		philo_eat(philo);
		if (interrupt(philo))
			return (NULL);
		philo_sleep(philo);
		if (interrupt(philo))
			return (NULL);
		philo_think(philo);
	}
}
