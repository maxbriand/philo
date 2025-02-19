/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 16:22:23 by mbriand           #+#    #+#             */
/*   Updated: 2024/07/31 17:23:29 by mbriand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_wait_end_meal(t_philos *philos)
{
	int	i;

	i = 0;
	while (i < philos->config->philo_nbr)
	{
		pthread_join(philos->nthread, NULL);
		philos = philos->next;
		i++;
	}
	pthread_mutex_lock(&philos->config->m_meal_is_ended);
	if (!philos->config->meal_is_ended)
		philos->config->meal_is_ended = 1;
	pthread_mutex_unlock(&philos->config->m_meal_is_ended);
}

static int	ft_launch_meal(t_philos *philos)
{
	int	i;

	i = 0;
	while (i < philos->config->philo_nbr)
	{
		if (pthread_create(&philos->nthread, NULL, ft_meal, philos))
			return (ft_perror("philo: pthread_create error"));
		philos = philos->next;
		i++;
	}
	return (0);
}

static void	ft_philo_alone(t_philos *philos)
{
	printf(CYAN"%d %d is thinking"RESET, ft_timestamp(philos), philos->i);
	ft_msleep(philos->config->die_time);
	printf(RED"%d %d died"RESET, ft_timestamp(philos), philos->i);
}

void	ft_exe(t_philos *philos)
{
	pthread_t	end_check;

	if (philos->config->philo_nbr == 1)
		return (ft_philo_alone(philos));
	if (ft_launch_meal(philos))
		return ;
	if (pthread_create(&end_check, NULL, ft_end_check, philos))
	{
		ft_perror("philo: pthread_create error");
		return ;
	}
	ft_wait_end_meal(philos);
	pthread_join(end_check, NULL);
}
