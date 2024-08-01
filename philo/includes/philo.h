/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 14:43:00 by egomez            #+#    #+#             */
/*   Updated: 2024/07/31 14:43:11 by egomez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>
#include <sys/time.h>

typedef struct	s_data
{
    int			n_philo;
    int 		time_to_die;
    int 		time_to_eat;
    int			time_to_sleep;
    int 		max_eat;
	long int	start_time;
	int			nb_of_eat;
}				t_data;

typedef struct	s_fork
{
	int				id_fork;
	pthread_mutex_t	fork;
}					t_fork;

typedef struct	s_philo
{
    int				id_philo;
	bool			is_dead;
	long int		last_eat;
	t_fork	*l_fork;
	t_fork	*r_fork;
}					t_philo;

int parsing(char **av, int ac);
int	ft_atoi(const char *nptr);

#endif
