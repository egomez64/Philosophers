/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 16:15:47 by egomez            #+#    #+#             */
/*   Updated: 2024/08/03 16:15:48 by egomez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static void	fork_msg(t_philo *philo)
{
	int	time;

	time = get_current_time() - philo->data->start_time;
	if (philo->data->is_dead)
		return ;
	pthread_mutex_lock(&philo->data->printf_mutex);
	printf("%d %d has taken a fork\n", time, philo->id_philo);
	pthread_mutex_unlock(&philo->data->printf_mutex);
}

void	wait_for_forks(t_philo *philo)
{
	if (philo->data->is_dead)
		return ;
	if (check_death(philo))
		return ;
	while (philo->nb_forks < 2)
	{
		if (check_death(philo))
			return ;
		pthread_mutex_lock(&philo->l_fork->fork_mutex);
		if (philo->l_fork->usable == 0)
		{
			fork_msg(philo);
			philo->l_fork->usable = 1;
			philo->nb_forks ++;
		}
		pthread_mutex_unlock(&philo->l_fork->fork_mutex);
		if (check_death(philo))
			return ;
		pthread_mutex_lock(&philo->r_fork->fork_mutex);
		if (philo->r_fork->usable == 0)
		{
			fork_msg(philo);
			philo->r_fork->usable = 1;
			philo->nb_forks ++;
		}
		pthread_mutex_unlock(&philo->r_fork->fork_mutex);
	}
}

int	check_satiety(t_philo *philo)
{
	int		i;

	i = 0;
	while (philo->data->n_philo > i)
	{
		pthread_mutex_lock(&philo->data->max_eat_mutex);
		if (philo->satiety < philo->data->max_eat)
		{
			pthread_mutex_unlock(&philo->data->max_eat_mutex);
			return (0);
		}
		pthread_mutex_unlock(&philo->data->max_eat_mutex);
		i++;
	}
	return (1);
}
