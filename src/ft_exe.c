/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 16:22:23 by mbriand           #+#    #+#             */
/*   Updated: 2024/07/21 23:51:35 by mbriand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*ft_meal(void *start)
{
	t_philos		*philos;
	struct timeval	*begin;

	philos = (t_philos *) start;
	begin = &philos->config->start;
	while (1)
	{	
		if (ft_thinking(philos, begin))
			break ;
		if (ft_eating(philos, begin))
			break ;
		gettimeofday(&philos->end_eat, NULL);
		if (ft_sleeping(philos, begin))
			break ;
	}
	return (NULL);
}

int	ft_exe(t_philos *philos)
{
	int	i;
	
	i = 0;
	while (i < philos->config->philo_nbr)
	{
		if (pthread_create(&philos->nthread, NULL, ft_meal, philos))
			return (1);
		philos = philos->next;
		i++;
	}
	i = 0;
	while (i < philos->config->philo_nbr)
	{
		pthread_join(philos->nthread, NULL);
		philos = philos->next;
		i++;
	}
	return (0);
}
