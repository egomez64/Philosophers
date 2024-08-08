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

void	handle_threads(t_philo *philo)
{
	int	i;
	int	check;

	i = 0;
	while (philo->data->n_philo > i)
	{
		//if(i%2 == 0)
		//{
			check = pthread_create(&philo->thread_id, NULL, (void *)&routine, &philo[i]);
			if (check != 0)
			{
				printf("philo %d : fail to be created\n", philo->id_philo);
				philo->data->is_dead = true;
				return ;
			}
		//}
		i++;
	}
	i = 0;
	i = 0;
	while (philo->data->n_philo > i)
	{
		pthread_join(philo[i].thread_id, NULL);
		i++;
	}
}
