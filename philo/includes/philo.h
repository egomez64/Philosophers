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
#include <sys/time.h>

typedef struct s_philo
{
    int	n_philo;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int max_eat;
}		t_philo;

int parsing(char **av, int ac);
int	ft_atoi(const char *nptr);

#endif
