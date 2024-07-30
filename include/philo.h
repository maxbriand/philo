/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 02:51:23 by mbriand           #+#    #+#             */
/*   Updated: 2024/07/30 17:20:37 by mbriand          ###   ########.fr       */
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

typedef struct s_config
{
	int				philo_nbr;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				eat_rep;
	int				six_args;
	int				meal_is_ended;
	pthread_mutex_t	m_meal_is_ended;
	pthread_mutex_t	m_printf;
	struct timeval	start;
}	t_config;

typedef struct s_philos
{
	pthread_mutex_t	m_fork;
	pthread_t		nthread;
	int				i;
	int				eat_counter;
	pthread_mutex_t	m_eat_counter;
	int				already_eat;
	pthread_mutex_t	m_already_eat;
	struct timeval	last_meal;
	pthread_mutex_t	m_last_meal;
	t_config		*config;
	struct s_philos	*next;
}	t_philos;

// parsing
int			ft_parsing(t_config *config, int ac, char **av);
int			ft_perror(char	*error);

// set structures
t_philos	*ft_set_philos(t_config *config);
void		ft_set_config(t_config *config, int ac, char **av);

// utils
int			ft_strlen(const char *s);
int			ft_is_posnbr(char *nbr);
int			ft_atoi(const char *nptr);
int			ft_timestamp(t_philos *philos);
void		ft_msleep(int ms);
int			ft_get_duration(t_philos *philos, struct timeval *time);

// exe
void		ft_exe(t_philos *philos);
void		*ft_meal(void *start);
void		ft_free_all(t_philos *philos);	

// states
int			ft_eating(t_philos *philos);
int			ft_sleeping(t_philos *philos);
int			ft_thinking(t_philos *philos);

// dead check
void		*ft_end_check(void *start);

#endif
