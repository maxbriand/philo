/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 01:22:30 by mbriand           #+#    #+#             */
/*   Updated: 2024/07/29 17:13:47 by mbriand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_free_all(t_philos *philos)
{
	int			i;
	int			philo_nbr;
	t_philos 	*last;
	
	i = 0;
	philo_nbr = philos->config->philo_nbr;
	while (i < philo_nbr)
	{
		pthread_mutex_destroy(&philos->m_fork);
		last = philos;
		philos = philos->next;
		free(last);
		i++;
	}
}
