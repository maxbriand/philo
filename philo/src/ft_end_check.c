/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_end_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 23:50:59 by mbriand           #+#    #+#             */
/*   Updated: 2024/07/31 18:37:09 by mbriand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_check_meal_limit(t_philos *philos)
{
	int	i;
	int	limit;

	if (!philos->config->six_args)
		return (0);
	limit = philos->config->eat_rep;
	i = 0;
	while (i < philos->config->philo_nbr)
	{
		pthread_mutex_lock(&philos->m_eat_counter);
		if (philos->eat_counter < limit)
		{
			pthread_mutex_unlock(&philos->m_eat_counter);
			return (0);
		}
		pthread_mutex_unlock(&philos->m_eat_counter);
		philos = philos->next;
		i++;
	}
	pthread_mutex_lock(&philos->config->m_meal_is_ended);
	philos->config->meal_is_ended = 1;
	pthread_mutex_unlock(&philos->config->m_meal_is_ended);
	return (1);
}

static void	ft_is_dead(t_philos *philos, int limit, struct timeval *last)
{
	int	duration;

	pthread_mutex_unlock(&philos->m_already_eat);
	duration = ft_get_duration(philos, last);
	if (duration > limit)
	{
		pthread_mutex_lock(&philos->config->m_meal_is_ended);
		philos->config->meal_is_ended = 1;
		pthread_mutex_unlock(&philos->config->m_meal_is_ended);
		pthread_mutex_lock(&philos->config->m_printf);
		printf(RED"%d %d died"RESET, ft_timestamp(philos), philos->i);
		pthread_mutex_unlock(&philos->config->m_printf);
	}
}

static int	ft_check_all_died(t_philos *philos)
{
	int	i;
	int	limit;

	limit = philos->config->die_time;
	i = 0;
	while (i < philos->config->philo_nbr)
	{
		pthread_mutex_lock(&philos->m_already_eat);
		if (!philos->already_eat)
			ft_is_dead(philos, limit, &philos->config->start);
		else
			ft_is_dead(philos, limit, &philos->last_meal);
		if (philos->config->meal_is_ended)
			return (1);
		philos = philos->next;
		i++;
	}
	return (0);
}

void	*ft_end_check(void *start)
{
	t_philos	*philos;

	philos = (t_philos *) start;
	while (1)
	{
		if (ft_check_all_died(philos))
			break ;
		if (ft_check_meal_limit(philos))
			break ;
		usleep(2);
	}
	return (NULL);
}
