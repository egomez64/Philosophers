/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 14:57:35 by egomez            #+#    #+#             */
/*   Updated: 2024/07/31 14:57:36 by egomez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	main(int ac, char **av)
{
	t_data	data;
	t_philo	*philo;

	if (!parsing(av, ac))
		return (1);
	init_data(&data, av);
	philo = ft_calloc(data.n_philo, sizeof(t_philo));
	if (!philo)
		return (1);
	data.forks = ft_calloc(data.n_philo, sizeof(t_fork));
	if (!data.forks)
		return (1);
	init_philo(philo, &data);
	init_mutex(&data);
	handle_threads(philo);
	destroy(&data, philo);
	free (philo);
	free (data.forks);
	return (0);
}
