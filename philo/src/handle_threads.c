/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 15:13:43 by egomez            #+#    #+#             */
/*   Updated: 2024/08/03 15:13:44 by egomez           ###   ########.fr       */
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

static int	thread_loop(t_philo *philo)
{
	int	i;

	i = 0;
	while (philo->data->n_philo > i)
	{
		if (pthread_create(&philo[i].thread_id, NULL,
				(void *)routine, &philo[i]))
		{
			printf("philo %d : fail to be created\n", philo->id_philo);
			philo->data->is_dead = true;
			break ;
		}
		i++;
	}
	return (i);
}

void	handle_threads(t_philo *philo)
{
	int	i;

	i = thread_loop(philo);
	if (i == philo->data->n_philo)
		supervisor(philo);
	while (i--)
		pthread_join(philo[i].thread_id, NULL);
}
