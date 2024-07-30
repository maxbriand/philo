/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 01:26:27 by mbriand           #+#    #+#             */
/*   Updated: 2024/07/31 00:44:00 by mbriand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_msleep_divider(t_philos *philos, int time)
{
	int	limit_ms;

	limit_ms = 1000;
	while (limit_ms < time)
	{
		ft_msleep(limit_ms);
		time -= limit_ms;
		if (ft_is_end(philos->config))
			return ;
	}
	ft_msleep(time);
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
