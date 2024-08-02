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
	pthread_mutex_lock(&philo->l_fork->fork_mutex);
	pthread_mutex_lock(&philo->r_fork->fork_mutex);
	printf("%zu %d is eating\n", get_current_time(), philo->id_philo);
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(&philo->r_fork->fork_mutex);
	pthread_mutex_unlock(&philo->l_fork->fork_mutex);
}
