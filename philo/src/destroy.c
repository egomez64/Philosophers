/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 16:15:26 by egomez            #+#    #+#             */
/*   Updated: 2024/08/02 16:15:27 by egomez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	destroy(t_data *data)
{
	int	i;

	i = 0;
	while (data->n_philo > i)
	{
		pthread_mutex_destroy(&data->forks->fork_mutex);
		i++;
	}
	pthread_mutex_destroy(&data->is_dead_mutex);
	i = 0;
	pthread_mutex_destroy(&data->printf_mutex);
	return (0);
}
