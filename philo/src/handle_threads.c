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

static int	load_thread(t_philo *philo, int i)
{
	if (pthread_create(&philo[i].thread_id, NULL,
			(void *)routine, &philo[i]))
	{
		printf("philo %d : fail to be created\n", philo->id_philo);
		philo->data->is_dead = true;
		return (1);
	}
	return (0);
}

static int	thread_loop(t_philo *philo)
{
	int	i;
	int	j;
	int	offset;
	int	n;

	n = 0;
	offset = 3;
	if (philo->data->n_philo % 2 == 0)
		offset = 2;
	j = 0;
	while (j < offset)
	{
		i = j;
		while (philo->data->n_philo > i)
		{
			if (load_thread(philo, i))
				break ;
			n++;
			i += offset;
		}
		j++;
		usleep(1000);
	}
	return (n);
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
