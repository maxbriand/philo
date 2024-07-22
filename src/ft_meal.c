/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_meal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 00:22:25 by mbriand           #+#    #+#             */
/*   Updated: 2024/07/22 20:35:47 by mbriand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_eating(t_philos *philos)
{
	if (ft_dead_check(philos, 1))
		return (1);
	gettimeofday(&philos->last_meal, NULL);
	printf("\033[1;35m%d %d is eating\033[0m\n", ft_timestamp(philos), philos->i);
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

int	ft_sleeping(t_philos *philos)
{
	printf("\033[1;33m%d %d is sleeping\033[0m\n", ft_timestamp(philos), philos->i);
	if (ft_sleep_n_dead_check(philos, philos->config->sleep_time, 1))
		return (1);
	return (0);
}

int	ft_thinking(t_philos *philos)
{
	if (ft_dead_check(philos, 1))
		return (1);
	printf("\033[1;36m%d %d is thinking\033[0m\n", ft_timestamp(philos), philos->i);
	if (philos->config->philo_nbr == 1 && ft_sleep_n_dead_check(philos, philos->config->die_time, 1))
		return (1);
	pthread_mutex_lock(philos->fork);
	pthread_mutex_lock(philos->next->fork);
	if (ft_dead_check(philos, 1))
		return (1);
	printf("\033[1;32m%d %d has taken a fork\033[0m\n", ft_timestamp(philos), philos->i);
	printf("\033[1;32m%d %d has taken a fork\033[0m\n", ft_timestamp(philos), philos->i);
	return (0);
}

void	*ft_meal(void *start)
{
	t_philos		*philos;

	philos = (t_philos *) start;
	while (1)
	{	
		if (ft_thinking(philos))
			break ;
		if (ft_eating(philos))
			break ;
		if (ft_sleeping(philos))
			break ;
	}
	return (NULL);
}
