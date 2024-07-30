/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_meal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 00:22:25 by mbriand           #+#    #+#             */
/*   Updated: 2024/07/31 00:52:40 by mbriand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_is_end(t_config *config)
{
	int	i;

	pthread_mutex_lock(&config->m_meal_is_ended);
	i = config->meal_is_ended;
	pthread_mutex_unlock(&config->m_meal_is_ended);
	return (i);
}

int	ft_eating(t_philos *philos)
{
	pthread_mutex_lock(&philos->config->m_printf);
	printf("\033[1;35m%d %d is eating\033[0m\n", \
		ft_timestamp(philos), philos->i);
	pthread_mutex_unlock(&philos->config->m_printf);
	pthread_mutex_lock(&philos->m_already_eat);
	philos->already_eat = 1;
	pthread_mutex_unlock(&philos->m_already_eat);
	pthread_mutex_lock(&philos->m_eat_counter);
	philos->eat_counter += 1;
	pthread_mutex_unlock(&philos->m_eat_counter);
	pthread_mutex_lock(&philos->m_last_meal);
	gettimeofday(&philos->last_meal, NULL);
	pthread_mutex_unlock(&philos->m_last_meal);
	ft_msleep_divider(philos, philos->config->eat_time);
	pthread_mutex_unlock(&philos->m_fork);
	pthread_mutex_unlock(&philos->next->m_fork);
	return (0);
}

int	ft_sleeping(t_philos *philos)
{
	pthread_mutex_lock(&philos->config->m_printf);
	printf("\033[1;33m%d %d is sleeping\033[0m\n", \
		ft_timestamp(philos), philos->i);
	pthread_mutex_unlock(&philos->config->m_printf);
	ft_msleep_divider(philos, philos->config->sleep_time);
	return (0);
}

int	ft_thinking(t_philos *philos)
{
	pthread_mutex_lock(&philos->config->m_printf);
	printf("\033[1;36m%d %d is thinking\033[0m\n", \
		ft_timestamp(philos), philos->i);
	pthread_mutex_unlock(&philos->config->m_printf);
	if (philos->i % 2 != 0)
	{
		ft_msleep(1);
		pthread_mutex_lock(&philos->next->m_fork);
		pthread_mutex_lock(&philos->m_fork);
	}
	else
	{
		pthread_mutex_lock(&philos->m_fork);
		pthread_mutex_lock(&philos->next->m_fork);
	}
	if (ft_is_end(philos->config))
		return (1);
	pthread_mutex_lock(&philos->config->m_printf);
	printf("\033[1;32m%d %d has taken a fork\033[0m\n", \
		ft_timestamp(philos), philos->i);
	printf("\033[1;32m%d %d has taken a fork\033[0m\n", \
		ft_timestamp(philos), philos->i);
	pthread_mutex_unlock(&philos->config->m_printf);
	return (0);
}

void	*ft_close_mutex(t_philos *philos)
{
	pthread_mutex_unlock(&philos->m_fork);
	pthread_mutex_unlock(&philos->next->m_fork);
	return (NULL);
}

void	*ft_meal(void *start)
{
	t_philos	*philos;
	int			i;

	philos = (t_philos *) start;
	while (1)
	{
		ft_thinking(philos);
		if (ft_is_end(philos->config))
			return (ft_close_mutex(philos));
		ft_eating(philos);
		if (ft_is_end(philos->config))
			break ;
		ft_sleeping(philos);
		if (ft_is_end(philos->config))
			break ;
		i++;
	}
	return (NULL);
}
