/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 15:04:02 by egomez            #+#    #+#             */
/*   Updated: 2024/08/08 15:04:03 by egomez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	print(t_philo *philo, char *str)
{
	unsigned long	time;

	time = get_current_time() - philo->data->start_time;
	printf("%zu %d %s\n", time, philo->id_philo, str);
}
