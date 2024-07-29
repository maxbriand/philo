/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_strucs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 18:29:48 by mbriand           #+#    #+#             */
/*   Updated: 2024/07/29 17:13:19 by mbriand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_philos	*ft_add_philo(t_config *config, int n)
{
	t_philos	*new;

	new = malloc(sizeof(t_philos));
	if (!new)
		return (NULL);
	new->i = n;
	new->config = config;
	new->already_eat = 0;
	new->eat_counter = 0;
	pthread_mutex_init(&new->m_fork, NULL);
	pthread_mutex_init(&new->m_last_meal, NULL);
	pthread_mutex_init(&new->m_eat_counter, NULL);
	new->next = NULL;
	return (new);
}

t_philos	*ft_set_philos(t_config *config)
{
	int			n;
	t_philos	*first;
	t_philos	*last;
	t_philos	*current;	

	n = 1;
	current = NULL;
	while (n <= config->philo_nbr)
	{
		last = current;
		if (!(current = ft_add_philo(config, n)))
		{
			// handle malloc error
			return (NULL);
		}
		if (last)
			last->next = current;
		if (n == 1)
			first = current;
		n++;
	}
	current->next = first;
	return (first);
}

void	ft_set_config(t_config *config, int ac, char **av)
{
	config->philo_nbr = ft_atoi(av[1]);
	config->die_time = ft_atoi(av[2]);
	config->eat_time = ft_atoi(av[3]);
	config->sleep_time = ft_atoi(av[4]);
	if (ac == 6)
	{
		config->six_args = 1;
		config->eat_rep = ft_atoi(av[5]);
	}
	else
		config->six_args = 0;
	config->meal_is_ended = 0;
	pthread_mutex_init(&config->m_meal_is_ended, NULL);
	gettimeofday(&config->start, NULL);
}
