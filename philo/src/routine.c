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

static void	philo_think(t_philo *philo)
{
	if (interrupt(philo))
		return ;
	print(philo, "is thinking");
}

static void	philo_sleep(t_philo *philo)
{
	if (interrupt(philo))
		return ;
	print(philo, "is sleeping");
	ft_usleep(philo->data->time_to_sleep, philo);
}

static void	lock_order(t_philo *philo)
{
	if (philo->id_philo % 2)
	{
		pthread_mutex_lock(&philo->l_fork->fork_mutex);
		if (!interrupt(philo))
			print(philo, "has taken a fork");
		pthread_mutex_lock(&philo->r_fork->fork_mutex);
		if (!interrupt(philo))
			print(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&philo->r_fork->fork_mutex);
		if (!interrupt(philo))
			print(philo, "has taken a fork");
		pthread_mutex_lock(&philo->l_fork->fork_mutex);
		if (!interrupt(philo))
			print(philo, "has taken a fork");
	}
}

static void	philo_eat(t_philo *philo)
{
	int	time;

	if (interrupt(philo))
		return ;
	time = (get_current_time() - philo->data->start_time) - philo->last_eat;
	while (philo->data->n_philo % 2 == 1 && time
		< (philo->data->time_to_eat * 3) && philo->satiety != 0)
	{
		if (interrupt(philo))
			return ;
	}
	lock_order(philo);
	if (!interrupt(philo))
	{
		print(philo, "is eating");
		pthread_mutex_lock(&philo->data->is_dead_mutex);
		philo->last_eat = get_current_time() - philo->data->start_time;
		pthread_mutex_unlock(&philo->data->is_dead_mutex);
		ft_usleep(philo->data->time_to_eat, philo);
		pthread_mutex_lock(&philo->data->is_dead_mutex);
		philo->satiety++;
		pthread_mutex_unlock(&philo->data->is_dead_mutex);
	}
	pthread_mutex_unlock(&philo->r_fork->fork_mutex);
	pthread_mutex_unlock(&philo->l_fork->fork_mutex);
}

void	*routine(t_philo *philo)
{
	if (philo->data->n_philo == 1)
	{
		print(philo, "has taken a fork");
		return (NULL);
	}
	philo_think(philo);
	while (1)
	{
		if (interrupt(philo))
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
