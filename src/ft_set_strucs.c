/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_strucs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 18:29:48 by mbriand           #+#    #+#             */
/*   Updated: 2024/07/31 00:38:41 by mbriand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_philos	*ft_new_philo(t_config *config, int n)
{
	t_philos	*new;

	new = malloc(sizeof(t_philos));
	if (!new)
		return (NULL);
	new->i = n;
	new->config = config;
	new->already_eat = 0;
	new->eat_counter = 0;
	new->next = NULL;
	return (new);
}

static int	ft_destroy_mutex(t_philos *philo, int n)
{
	if (n == 1)
		pthread_mutex_destroy(&philo->m_already_eat);
	if (n == 2)
	{
		pthread_mutex_destroy(&philo->m_already_eat);
		pthread_mutex_destroy(&philo->m_fork);
	}
	if (n == 3)
	{
		pthread_mutex_destroy(&philo->m_already_eat);
		pthread_mutex_destroy(&philo->m_fork);
		pthread_mutex_destroy(&philo->m_last_meal);		
	}
	return (1);
}

static int	ft_init_mutex_philo(t_philos *philo)
{
	if (pthread_mutex_init(&philo->m_already_eat, NULL))
		return (1);
	if (pthread_mutex_init(&philo->m_fork, NULL))
		return (ft_destroy_mutex(philo, 1));
	if (pthread_mutex_init(&philo->m_last_meal, NULL))
		return (ft_destroy_mutex(philo, 2));
	if (pthread_mutex_init(&philo->m_eat_counter, NULL))
		return (ft_destroy_mutex(philo, 3));
	return (0);
}

static void	*ft_set_issue(t_philos *first, t_philos *current)
{
	if (current)
	{
		ft_perror("philo: mutex init issue");
		free(current);
	}
	else
		ft_perror("philo: malloc error");
	ft_free_all(first);
	return (NULL);
}

t_philos	*ft_set_philos(t_config *config)
{
	int			n;
	t_philos	*first;
	t_philos	*last;
	t_philos	*current;	

	n = 1;
	current = NULL;
	first = NULL;
	while (n <= config->philo_nbr)
	{
		last = current;
		current = ft_new_philo(config, n);
		if (!current)
			return (ft_set_issue(first, current));
		if (ft_init_mutex_philo(current))
			return (ft_set_issue(first, current));
		if (last)
			last->next = current;
		if (n == 1)
			first = current;
		n++;
	}
	current->next = first;
	return (first);
}

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
