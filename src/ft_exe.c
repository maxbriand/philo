/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 16:22:23 by mbriand           #+#    #+#             */
/*   Updated: 2024/07/23 18:13:19 by mbriand          ###   ########.fr       */
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
}

static int	ft_launch_meal(t_philos *philos)
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
	return (0);
}

void	ft_exe(t_philos *philos)
{
	pthread_t	end_check;
	
	if (ft_launch_meal(philos))
		return ;
	// pthread_create(&end_check, NULL, ft_end_check);
	ft_wait_end_meal(philos);
	// pthread_join(end_check, NULL);
}
