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

typedef struct	s_fork
{
	int				usable;
	pthread_mutex_t	fork_mutex;
}					t_fork;

typedef struct	s_data
{
    int					n_philo;
    int 				time_to_die;
    int 				time_to_eat;
    int					time_to_sleep;
    int 				max_eat;
	bool				is_dead;
	long int			start_time;
	int					satiety;
	t_fork				*forks;
	pthread_mutex_t		is_dead_mutex;
	pthread_mutex_t		philo_satiety_mutex;
	pthread_mutex_t		printf_mutex;
}						t_data;

typedef struct	s_philo
{
	t_data			*data;
    int				id_philo;
	long int		last_eat;
	int				nb_forks;
	pthread_t		thread_id;
	t_fork	*l_fork;
	t_fork	*r_fork;
}					t_philo;

int		parsing(char **av, int ac);

int		init_data(t_data *data, char **av);
void	init_philo(t_philo *philo, t_data *data);
int		init_mutex(t_data *data);

void	handle_threads(t_philo *philo);

int		check_death(t_philo *philo);
void	wait_for_forks(t_philo *philo);
void	philo_think(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	philo_eat(t_philo *philo);
void	*routine(t_philo *philo);

int		destroy(t_data *data);

int		ft_atoi(const char *nptr);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
size_t	get_current_time(void);
int		ft_usleep(size_t milliseconds);

#endif
