/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 16:54:13 by egomez            #+#    #+#             */
/*   Updated: 2024/07/31 16:54:18 by egomez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	ft_atoi(const char *nptr)
{
	int	conv;
	int	i;
	int	sign;

	conv = 0;
	i = 0;
	sign = 1;
	while (*nptr && ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign *= -1;
		i++;
	}
	if (nptr[i] < '0' || nptr[i] > '9')
		return (0);
	while (*nptr && nptr[i] >= '0' && nptr[i] <= '9')
	{
		conv = conv * 10 + (nptr[i] - '0');
		i++;
	}
	return (conv * sign);
}
