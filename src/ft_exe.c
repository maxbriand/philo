/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 16:22:23 by mbriand           #+#    #+#             */
/*   Updated: 2024/07/22 20:47:38 by mbriand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_wait_meal_end(t_philos *philos)
{
	int	i;
	
	i = 0;
	while (i < philos->config->philo_nbr)
	{
		pthread_join(philos->nthread, NULL);
		philos = philos->next;
		// printf("the end of %d is at %d\n", philos->i, ft_timestamp(philos));
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

static int	ft_launch_monitoring(t_philos *philos)
{


}

static void	ft_wait_monitoring()
{


}

void	ft_exe(t_philos *philos)
{
	if (ft_launch_meal(philos))
		return ;
	if (ft_launch_monitoring(philos->config))
		return ;
	ft_wait_meal_end(philos);
	ft_wait_monitoring(philos->congig);
}
