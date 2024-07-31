/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_config.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 15:42:23 by mbriand           #+#    #+#             */
/*   Updated: 2024/07/31 15:42:40 by mbriand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_set_config(t_config *config, int ac, char **av)
{
	config->philo_nbr = ft_atol(av[1]);
	config->die_time = ft_atol(av[2]);
	config->eat_time = ft_atol(av[3]);
	config->sleep_time = ft_atol(av[4]);
	if (ac == 6)
	{
		config->six_args = 1;
		config->eat_rep = ft_atol(av[5]);
	}
	else
		config->six_args = 0;
	config->meal_is_ended = 0;
	if (pthread_mutex_init(&config->m_meal_is_ended, NULL))
		return (ft_perror("philo: mutex init issue"));
	if (pthread_mutex_init(&config->m_printf, NULL))
	{
		pthread_mutex_destroy(&config->m_meal_is_ended);
		return (ft_perror("philo: mutex init issue"));
	}
	gettimeofday(&config->start, NULL);
	return (0);
}
