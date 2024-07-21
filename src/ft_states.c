/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_states.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 20:20:05 by mbriand           #+#    #+#             */
/*   Updated: 2024/07/21 23:49:04 by mbriand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_eating(t_philos *philos, struct timeval *begin)
{
	printf("%d %d is eating\n", ft_timestamp(*begin), philos->i);
	if(ft_sleep_n_dead_check(philos, philos->config->eat_time, 0))
	{
		pthread_mutex_unlock(philos->fork);
		pthread_mutex_unlock(philos->next->fork);
		return (1);
	}
	pthread_mutex_unlock(philos->fork);
	pthread_mutex_unlock(philos->next->fork);
	if (!philos->already_eat)
		philos->already_eat = 1;
	return (0);
}

int	ft_sleeping(t_philos *philos, struct timeval *begin)
{
	printf("%d %d is sleeping\n", ft_timestamp(*begin), philos->i);
	if (ft_sleep_n_dead_check(philos, philos->config->sleep_time, 1))
		return (1);
	return (0);
}

int	ft_thinking(t_philos *philos, struct timeval *begin)
{
	printf("%d %d is thinking\n", ft_timestamp(*begin), philos->i);
	if (philos->config->philo_nbr == 1 && ft_sleep_n_dead_check(philos, philos->config->die_time, 1))
		return (1);
	pthread_mutex_lock(philos->fork);
	pthread_mutex_lock(philos->next->fork);
	if (ft_dead_check(philos, 1))
		return (1);
	printf("%d %d has taken a fork\n", ft_timestamp(*begin), philos->i);
	printf("%d %d has taken a fork\n", ft_timestamp(*begin), philos->i);
	return (0);
}
