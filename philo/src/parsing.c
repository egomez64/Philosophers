/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 16:53:47 by egomez            #+#    #+#             */
/*   Updated: 2024/07/31 16:53:50 by egomez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static void	err(int nb)
{
	if (nb == 0)
		printf("error : too much or too few arguments !\n");
	else if (nb == 1)
		printf("error : the arguments have to be numerics !\n");
	else if (nb == 2)
		printf("error : the arguments have to be positive !\n");
	else if (nb == 3)
		printf("error : there is more than 200 philosophers or less than 1 eat !\n");
}

int parsing(char **av, int ac)
{
	int i;
	int y;

	if (!ac || ac < 5 || ac > 6)
	{
		err(0);
		return (0);
	}
	i = 1;
	while(av[i])
	{
		y = 0;
		while (av[i][y])
		{
			if ((av[i][y] < '0' || av[i][y] > '9') && av[i][y] != '-')
			{
				err(1);
				return (0);
			}
			y++;
		}
		i++;
	}
	i = 1;
	while (av[i])
	{
		if (ft_atoi(av[i]) < 1)
		{
			err(2);
			return (0);
		}
		i++;
	}
	if ((ft_atoi(av[1]) > 200) || (av[5] && ft_atoi(av[5]) < 1))
	{
		err(3);
		return (0);
	}
	return (1);
}

