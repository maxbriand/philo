/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 01:17:03 by mbriand           #+#    #+#             */
/*   Updated: 2024/07/27 21:00:18 by mbriand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_scope_args(t_config *config)
{
	if (config->philo_nbr < 1 || config->philo_nbr > 200)
		return (ft_perror("philo: scope of philosophers is between 1 and 200"));
	if (config->die_time < 60)
		return (ft_perror("philo: the time to die should be at least 60ms"));
	if (config->eat_time < 60)
		return (ft_perror("philo: the time to eat should be at least 60ms"));
	if (config->sleep_time < 60)
		return (ft_perror("philo: the time to sleep should be at least 60ms"));
	if (config->six_args && config->eat_rep < 1)
		return (ft_perror("philo: philosophers have to eat at least 1 time"));
	return (0);
}

static int	ft_are_pos_nbr(char **av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (!ft_is_posnbr(av[i]))
		{
			ft_perror("philo: arguments aren't only positive numbers");
			return (1);
		}
		i++;
	}
	return (0);
}

static int	ft_nbr_of_arg(int ac)
{
	if (ac != 5 && ac != 6)
	{
		if (ac < 5)
			ft_perror("philo: too few arguments");
		if (ac > 6)
			ft_perror("philo: too many arguments");
		return (1);
	}
	return (0);
}

int	ft_parsing(t_config *config, int ac, char **av)
{
	if (ft_nbr_of_arg(ac))
		return (1);
	if (ft_are_pos_nbr(av))
		return (1);
	ft_set_config(config, ac, av);
	if (ft_scope_args(config))
		return (1);
	return (0);
}
