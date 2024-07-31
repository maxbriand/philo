/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 15:40:47 by mbriand           #+#    #+#             */
/*   Updated: 2024/07/31 15:43:17 by mbriand          ###   ########.fr       */
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

void	*ft_close_mutex(t_philos *philos)
{
	pthread_mutex_unlock(&philos->m_fork);
	pthread_mutex_unlock(&philos->next->m_fork);
	return (NULL);
}
