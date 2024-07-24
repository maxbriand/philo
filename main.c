/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 01:29:27 by mbriand           #+#    #+#             */
/*   Updated: 2024/07/23 01:58:32 by mbriand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int ac, char **av)
{
	t_philos	*philos;
	t_config	config;

	if (ft_parsing(&config, ac, av))
		return (1);
	if (!(philos = ft_set_philos(&config)))
		return (1);
	ft_exe(philos);
	ft_free_all(philos);
	return (0);
}
