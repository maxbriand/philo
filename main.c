/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 01:29:27 by mbriand           #+#    #+#             */
/*   Updated: 2024/07/20 17:24:43 by mbriand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// ./philo 2number_of_philo 3time_to_die 4time_to_eat 5time_to_sleep 6number_of_eat
int main(int ac, char **av)
{
	t_philos	*philos;
	t_config	config;

	if (ft_parsing(&config, ac, av))
		return (1);
	//printf("doesn't stop after parsing part!!!!!!!!!!!\n");
	if (!(philos = ft_set_philos(&config)))
		return (1);
	if (ft_exe(philos))
		return (1);
	ft_free_all(philos);
	return (0);
}
