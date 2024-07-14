/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 02:51:23 by mbriand           #+#    #+#             */
/*   Updated: 2024/07/14 02:09:01 by mbriand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

// parsing
int		ft_parsing(int ac, char **av);
void	ft_perror(char *error);

// utils
int	ft_strlen(const char *s);
int	ft_is_posnbr(char *nbr);
int	ft_atoi(const char *nptr);

// typedef	struct s_philos
// {
// 	int	i; // ?
// 	struct s_philos	*next;
// } t_philos;

#endif