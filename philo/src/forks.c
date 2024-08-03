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

	time = get_current_time();
	pthread_mutex_lock(&philo->data->printf_mutex);
	printf("%d %d has taken a fork\n", time, philo->id_philo);
	pthread_mutex_unlock(&philo->data->printf_mutex);
}

void	wait_for_forks(t_philo *philo)
{
	if (check_death(philo))
		return ;
	while (philo->nb_forks < 2)
	{
		if (check_death(philo)
		|| (philo->data->max_eat
			&& (philo->data->satiety >= philo->data->max_eat)))
			return ;
		pthread_mutex_lock(&philo->l_fork->fork_mutex);
		if (philo->l_fork->usable == 0)
		{
			fork_msg(philo);
			philo->nb_forks ++;
		}
		if (check_death(philo)
		|| (philo->data->max_eat
			&& (philo->data->satiety >= philo->data->max_eat)))
			return ;
		pthread_mutex_lock(&philo->r_fork->fork_mutex);
		if (philo->r_fork->usable == 0)
		{
			fork_msg(philo);
			philo->nb_forks ++;
		}
	}
}
