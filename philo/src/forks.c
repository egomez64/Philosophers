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

static int	start_l(t_philo *philo)
{
	if (philo->l_fork->usable == 0)
	{
		fork_msg(philo);
		philo->l_fork->usable = 1;
	}
	if (interrupt(philo))
	{
		philo->l_fork->usable = 0;
		return (0);
	}
	if (philo->r_fork->usable == 0)
	{
		fork_msg(philo);
		philo->r_fork->usable = 1;
	}
	return (1);
}

static int	start_r(t_philo *philo)
{
	if (philo->r_fork->usable == 0)
	{
		fork_msg(philo);
		philo->r_fork->usable = 1;
	}
	if (interrupt(philo))
	{
		philo->r_fork->usable = 0;
		return (0);
	}
	if (philo->l_fork->usable == 0)
	{
		fork_msg(philo);
		philo->l_fork->usable = 1;
	}
	return (1);
}

static int	handle_foks(t_philo *philo)
{
	int	res;

	if (philo->id_philo % 2)
		res = start_l(philo);
	else
		res = start_r(philo);
	return (res);
}

static void	one_wait_for_fork(t_philo *philo)
{
	if (interrupt(philo))
		return ;
	pthread_mutex_lock(&philo->l_fork->fork_mutex);
	if (interrupt(philo))
	{
		pthread_mutex_unlock(&philo->l_fork->fork_mutex);
		return ;
	}
	fork_msg(philo);
	philo->l_fork->usable = 1;
	pthread_mutex_unlock(&philo->l_fork->fork_mutex);
}

void	wait_for_forks(t_philo *philo)
{
	int	res;

	if (philo->data->n_philo == 1)
	{
		one_wait_for_fork(philo);
		return ;
	}
	pthread_mutex_lock(&philo->l_fork->fork_mutex);
	pthread_mutex_lock(&philo->r_fork->fork_mutex);
	while (!interrupt(philo))
	{
		if (philo->l_fork->usable || philo->r_fork->usable)
		{
			pthread_mutex_unlock(&philo->r_fork->fork_mutex);
			pthread_mutex_unlock(&philo->l_fork->fork_mutex);
			continue ;
		}
		res = handle_foks(philo);
		pthread_mutex_unlock(&philo->r_fork->fork_mutex);
		pthread_mutex_unlock(&philo->l_fork->fork_mutex);
		if (res)
			break ;
	}
}
