/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 01:26:27 by mbriand           #+#    #+#             */
/*   Updated: 2024/07/30 18:29:42 by mbriand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isspace(int c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

static long	ft_handle_sign(const char *sign, long nbr)
{
	if (*sign == '-')
		nbr *= -1;
	return (nbr);
}

long	ft_atol(const char *s)
{
	long		nbr;
	const char	*sign;
	int			digit;	

	nbr = 0;
	while (ft_isspace(*s) == 1)
		s++;
	sign = s;
	if (*s == '-' || *s == '+')
		s++;
	while (*s)
	{
		digit = *s - '0';
		if ((((LONG_MAX / 10 == nbr) && digit > LONG_MAX % 10)
				|| (LONG_MAX / 10 < nbr)) && *sign != '-')
			return (LONG_MAX);
		if ((((LONG_MIN / 10 == -nbr) && - digit < LONG_MIN % 10)
				|| (LONG_MIN / 10 > -nbr)) && *sign == '-')
			return (LONG_MIN);
		nbr *= 10;
		nbr += (*s) - 48;
		s++;
	}
	nbr = ft_handle_sign(sign, nbr);
	return (nbr);
}

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

int	ft_get_duration(t_philos *philos, struct timeval *time)
{
	int				duration;
	struct timeval	current;

	gettimeofday(&current, NULL);
	pthread_mutex_lock(&philos->m_last_meal);
	duration = (current.tv_sec - time->tv_sec) * 1000;
	duration += (current.tv_usec - time->tv_usec) / 1000;
	pthread_mutex_unlock(&philos->m_last_meal);
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
