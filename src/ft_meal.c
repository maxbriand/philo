/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_meal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 00:22:25 by mbriand           #+#    #+#             */
/*   Updated: 2024/07/22 00:22:45 by mbriand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		gettimeofday(&philos->end_eat, NULL);
		if (ft_sleeping(philos))
			break ;
	}
	return (NULL);
}