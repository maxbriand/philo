/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 01:22:30 by mbriand           #+#    #+#             */
/*   Updated: 2024/07/29 18:45:28 by mbriand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_free_all(t_philos *philos)
{
	int			i;
	int			philo_nbr;
	t_philos	*last;

	i = 0;
	pthread_mutex_destroy(&philos->config->m_meal_is_ended);
	pthread_mutex_destroy(&philos->config->m_printf);
	philo_nbr = philos->config->philo_nbr;
	while (i < philo_nbr)
	{
		pthread_mutex_destroy(&philos->m_fork);
		pthread_mutex_destroy(&philos->m_already_eat);
		pthread_mutex_destroy(&philos->m_eat_counter);
		pthread_mutex_destroy(&philos->m_last_meal);
		last = philos;
		philos = philos->next;
		free(last);
		i++;
	}
}
