/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_meal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 00:22:25 by mbriand           #+#    #+#             */
/*   Updated: 2024/07/29 17:14:20 by mbriand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int ft_is_end(t_config *config)
{
	int i;

	pthread_mutex_lock(&config->m_meal_is_ended);
	i = config->meal_is_ended;
	pthread_mutex_unlock(&config->m_meal_is_ended);
	return (i);
}

void	ft_msleep_divider(t_philos *philos, int time)
{
	int limit_ms;

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

int ft_eating(t_philos *philos)
{
	printf("\033[1;35m%d %d is eating\033[0m\n", ft_timestamp(philos), philos->i);
	philos->already_eat = 1;
	gettimeofday(&philos->last_meal, NULL);
	ft_msleep_divider(philos, philos->config->eat_time);
	pthread_mutex_unlock(&philos->m_fork);
	pthread_mutex_unlock(&philos->next->m_fork);
	pthread_mutex_lock(&philos->m_eat_counter);
	philos->eat_counter += 1;
	pthread_mutex_unlock(&philos->m_eat_counter);	
	return (0);
}

int ft_sleeping(t_philos *philos)
{
	printf("\033[1;33m%d %d is sleeping\033[0m\n", ft_timestamp(philos), philos->i);
	ft_msleep_divider(philos, philos->config->sleep_time);
	return (0);
}

int ft_thinking(t_philos *philos)
{
	printf("\033[1;36m%d %d is thinking\033[0m\n", ft_timestamp(philos), philos->i);
	if (philos->i % 2 == 0)
		ft_msleep(1);
	pthread_mutex_lock(&philos->m_fork);
	pthread_mutex_lock(&philos->next->m_fork);
	if (ft_is_end(philos->config))
		return (1);
	printf("\033[1;32m%d %d has taken a fork\033[0m\n", ft_timestamp(philos), philos->i);
	printf("\033[1;32m%d %d has taken a fork\033[0m\n", ft_timestamp(philos), philos->i);
	return (0);
}

void *ft_close_mutex(t_philos *philos)
{
	pthread_mutex_unlock(&philos->m_fork);
	pthread_mutex_unlock(&philos->next->m_fork);
	return (NULL);
}

void *ft_meal(void *start)
{
	t_philos 	*philos;
	int			i;

	philos = (t_philos *) start;
	while (1)
	{
		ft_thinking(philos);
		if (ft_is_end(philos->config))
			return (ft_close_mutex(philos));
		ft_eating(philos);
		if (ft_is_end(philos->config))
			break;
		ft_sleeping(philos);
		if (ft_is_end(philos->config))
			break;
		i++;
	}
	return (NULL);
}
