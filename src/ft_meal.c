/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_meal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 00:22:25 by mbriand           #+#    #+#             */
/*   Updated: 2024/07/24 17:45:05 by mbriand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int ft_is_end(t_config *config)
{
	int i;

	pthread_mutex_lock(&config->m_someone_dead);
	i = config->someone_dead;
	pthread_mutex_unlock(&config->m_someone_dead);
	return (i);
}

int ft_eating(t_philos *philos)
{
	//printf("%d %d is eating\n", ft_timestamp(philos), philos->i);
	usleep(philos->config->eat_time);
	pthread_mutex_unlock(philos->fork);
	pthread_mutex_unlock(philos->next->fork);
	return (0);
}

// printf("\033[1;33m%d %d is sleeping\033[0m\n", ft_timestamp(philos), philos->i);

int ft_sleeping(t_philos *philos)
{
	// printf("%d %d is sleeping\n", ft_timestamp(philos), philos->i);
	usleep(philos->config->sleep_time);
	return (0);
}

// printf("\033[1;36m%d %d is thinking\033[0m\n", ft_timestamp(philos), philos->i);
// printf("\033[1;32m%d %d has taken a fork\033[0m\n", ft_timestamp(philos), philos->i);
// printf("\033[1;32m%d %d has taken a fork\033[0m\n", ft_timestamp(philos), philos->i);

int ft_thinking(t_philos *philos)
{
	// printf("%d %d is thinking\n", ft_timestamp(philos), philos->i);
	// if (philos->i % 2 == 0)
	// 	ft_msleep(1);
	pthread_mutex_lock(philos->fork);
	pthread_mutex_lock(philos->next->fork);
	// printf("%d %d has taken a fork\n", ft_timestamp(philos), philos->i);
	// printf("%d %d has taken a fork\n", ft_timestamp(philos), philos->i);
	return (0);
}

void *ft_close_mutex(t_philos *philos)
{
	pthread_mutex_unlock(philos->fork);
	pthread_mutex_unlock(philos->next->fork);
	return (NULL);
}

void *ft_meal(void *start)
{
	t_philos 	*philos;
	int			i;

	//tests
	struct timeval zero;

	philos = (t_philos *)start;
	while (1)
	{
		// tests
		gettimeofday(&zero, NULL);

		if (philos->config->six_args && i == philos->config->eat_rep)
			break ;
		// ft_write_time(philos, zero, "before", 0);

		gettimeofday(&zero, NULL);

		ft_thinking(philos);
		if (ft_is_end(philos->config))
			return (ft_close_mutex(philos));
		ft_write_time(philos, zero, "think", 0);

		gettimeofday(&zero, NULL);

		ft_eating(philos);
		if (ft_is_end(philos->config))
			break;
		// ft_write_time(philos, zero, "eat", 100000);
		
		gettimeofday(&zero, NULL);

		ft_sleeping(philos);
		if (ft_is_end(philos->config))
			break;
		// ft_write_time(philos, zero, "sleep", 100000);
		i++;
	}
	return (NULL);
}

// void *ft_meal(void *start)
// {
// 	t_philos *philos;

// 	while (1)
// 	{
// 		philos = (t_philos *)start;
// 		pthread_mutex_lock(philos->fork);
// 		pthread_mutex_lock(philos->next->fork);
// 		// printf("%d %d is eating\n", ft_timestamp(philos), philos->i);
// 		printf("%d\n", ft_timestamp(philos));
// 		usleep(philos->config->eat_time);
// 		pthread_mutex_unlock(philos->fork);
// 		pthread_mutex_unlock(philos->next->fork);
// 		usleep(philos->config->sleep_time);
// 	}
// 	return (NULL);
// }
