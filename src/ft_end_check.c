/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_end_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 23:50:59 by mbriand           #+#    #+#             */
/*   Updated: 2024/07/29 17:22:55 by mbriand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_if_already_eat(t_philos *philos, int limit)
{
	int	duration;
	
	pthread_mutex_lock(&philos->m_last_meal);
	duration = ft_get_duration(&philos->last_meal);
	pthread_mutex_unlock(&philos->m_last_meal);
	if (duration > limit)
	{
		pthread_mutex_lock(&philos->config->m_meal_is_ended);
		philos->config->meal_is_ended = 1;
		pthread_mutex_unlock(&philos->config->m_meal_is_ended);
		printf("\033[1;31m%d %d died\033[0m\n", ft_timestamp(philos), philos->i);
	}
}

static void	ft_if_didnt_eat(t_philos *philos, int limit)
{
	int	duration;
	
	duration = ft_get_duration(&philos->config->start);
	if (duration > limit)
	{
		pthread_mutex_lock(&philos->config->m_meal_is_ended);
		philos->config->meal_is_ended = 1;
		pthread_mutex_unlock(&philos->config->m_meal_is_ended);
		printf("\033[1;31m%d %d died\033[0m\n", ft_timestamp(philos), philos->i);
	}
}

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
		if (philos->eat_counter < limit)
			return (0);
		philos = philos->next;
		i++;
	}
	pthread_mutex_lock(&philos->config->m_meal_is_ended);
	philos->config->meal_is_ended = 1;
	pthread_mutex_unlock(&philos->config->m_meal_is_ended);
	return (1);
}

static int	ft_check_all_died(t_philos *philos)
{
	int	i;
	int	limit;

	// printf("the number of philo is: %d\n", philos->config->philo_nbr);	
	limit = philos->config->die_time;
	i = 0;
	while (i < philos->config->philo_nbr)
	{
		// add mutex
		if (!philos->already_eat)
			ft_if_didnt_eat(philos, limit);			
		else
			ft_if_already_eat(philos, limit);
		// use mutex?
		if (philos->config->meal_is_ended)
			return (1);
		i++;
	}
	return (0);
}

void	*ft_end_check(void *start)
{
	t_philos *philos;

	philos = (t_philos *) start;
	while (1)
	{
		if (ft_check_all_died(philos))
			break ;
		if (ft_check_meal_limit(philos))
			break;
		ft_msleep(1);
	}	
	return (NULL);
}
