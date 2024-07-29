/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 01:26:27 by mbriand           #+#    #+#             */
/*   Updated: 2024/07/29 18:43:25 by mbriand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_timestamp(t_philos *philos)
{
	int				timestamp;
	struct timeval	current;
	struct timeval	start;

	start = philos->config->start;
	gettimeofday(&current, NULL);
	timestamp = (current.tv_sec - start.tv_sec) * 1000;
	timestamp += (current.tv_usec - start.tv_usec) / 1000;
	return (timestamp);
}

int	ft_get_duration(struct timeval *time)
{
	int				duration;
	struct timeval	current;

	gettimeofday(&current, NULL);
	duration = (current.tv_sec - time->tv_sec) * 1000;
	duration += (current.tv_usec - time->tv_usec) / 1000;
	return (duration);
}

int	ft_is_posnbr(char *nbr)
{
	if (*nbr == '+')
		nbr++;
	while (*nbr)
	{
		if (*nbr < '0' || *nbr > '9')
			return (0);
		nbr++;
	}
	return (1);
}

int	ft_atoi(const char *nptr)
{
	char	test;
	int		i;
	int		total;

	i = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == ' ')
		i++;
	test = nptr[i];
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		test = nptr[i];
		i++;
	}
	total = 0;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		total *= 10;
		total += (nptr[i] - 48);
		i++;
	}
	if (test == '-')
		total *= -1;
	return (total);
}

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_msleep(int ms)
{
	ms *= 1000;
	usleep(ms);
}
