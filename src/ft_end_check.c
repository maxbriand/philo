/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_die_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 23:50:59 by mbriand           #+#    #+#             */
/*   Updated: 2024/07/22 20:37:50 by mbriand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_is_dead(t_philos *philos)
{
	struct timeval	current;
	int				duration;

	gettimeofday(&current, NULL);
	if (!philos->already_eat)
	{
		duration = (current.tv_sec - philos->config->start.tv_sec) * 1000;
		duration += (current.tv_usec - philos->config->start.tv_usec) / 1000;
	}
	else
	{
		duration = (current.tv_sec - philos->last_meal.tv_sec) * 1000;
		duration += (current.tv_usec - philos->last_meal.tv_usec) / 1000;
	}
	if (duration > philos->config->die_time)
		return (1);
	return (0);
}

int	ft_dead_check(t_philos *philos, int a)
{
	// another philosopher is dead
	if (philos->config->someone_dead)
	{
		pthread_mutex_unlock(philos->fork);
		pthread_mutex_unlock(philos->next->fork);
		return (1);		
	}
	// this philosopher is dead
	if (a == 1 && ft_is_dead(philos))
	{
		printf("\033[1;31m%d %d died\033[0m\n", ft_timestamp(philos), philos->i);
		// protect this value using mutex
		philos->config->someone_dead = 1;
		return (1);
	}
	return (0);
}

int	ft_sleep_n_dead_check(t_philos *philos, int stime, int a)
{
	int	time_check;
	
	// if (philos->config->philo_nbr == 1)
	// {
	// 	stime *= 1000;
	// 	stime += 2000;
	// }
	// time_check = 10000;
	// // while (stime > 0)
	// while (1)
	// {
	// 	if (ft_dead_check(philos, a))
	// 		return (1);
	// 	if (ft_dead_check(philos->next, 1))
	// 		return (1);
	// 	if (stime < time_check)
	// 	{
	// 		usleep(stime);
	// 		stime = 0;
	// 		break ;
	// 	}
	// 	// printf("timestamp = %d\n", ft_timestamp(philos));
	// 	usleep(time_check);
	// 	stime -= time_check;
	// }
	if (ft_dead_check(philos, a))
			return (1);
	if (ft_dead_check(philos->next, 1))
		return (1);
	usleep(stime);
	if (ft_dead_check(philos, a))
			return (1);
	if (ft_dead_check(philos->next, 1))
		return (1);
	return (0);
}
