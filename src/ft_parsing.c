/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 01:17:03 by mbriand           #+#    #+#             */
/*   Updated: 2024/07/14 02:09:27 by mbriand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_arg_are_posnbr(char **av)
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

static int	ft_arg_nbr(int ac)
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

int	ft_parsing(int ac, char **av)
{
	if (ft_arg_nbr(ac))
		return (1);
	if (ft_arg_are_posnbr(av))
		return (1);
	return (0);	
}
