/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_meal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriand <mbriand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 00:22:25 by mbriand           #+#    #+#             */
/*   Updated: 2024/08/03 19:22:34 by mbriand          ###   ########.fr       */
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
	printf(MAGENTA"%d %d is eating"RESET, ft_timestamp(philos), philos->i);
	pthread_mutex_unlock(&philos->config->m_printf);
	pthread_mutex_lock(&philos->m_already_eat);
	philos->already_eat = 1;
	pthread_mutex_unlock(&philos->m_already_eat);
	pthread_mutex_lock(&philos->m_last_meal);
	gettimeofday(&philos->last_meal, NULL);
	pthread_mutex_unlock(&philos->m_last_meal);
	ft_msleep_divider(philos, philos->config->eat_time);
	pthread_mutex_lock(&philos->m_eat_counter);
	philos->eat_counter += 1;
	pthread_mutex_unlock(&philos->m_eat_counter);
	pthread_mutex_unlock(&philos->m_fork);
	pthread_mutex_unlock(&philos->next->m_fork);
	return (0);
}

int	ft_sleeping(t_philos *philos)
{
	pthread_mutex_lock(&philos->config->m_printf);
	printf(YELLOW"%d %d is sleeping"RESET, ft_timestamp(philos), philos->i);
	pthread_mutex_unlock(&philos->config->m_printf);
	ft_msleep_divider(philos, philos->config->sleep_time);
	return (0);
}

int	ft_thinking(t_philos *philos)
{
	pthread_mutex_lock(&philos->config->m_printf);
	printf(CYAN"%d %d is thinking"RESET, ft_timestamp(philos), philos->i);
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
	printf(GREEN"%d %d has taken a fork"RESET, ft_timestamp(philos), philos->i);
	printf(GREEN"%d %d has taken a fork"RESET, ft_timestamp(philos), philos->i);
	pthread_mutex_unlock(&philos->config->m_printf);
	return (0);
}

void	*ft_meal(void *start)
{
	t_philos	*philos;

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
	}
	return (NULL);
}
