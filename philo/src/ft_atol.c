/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 00:41:50 by mbriand           #+#    #+#             */
/*   Updated: 2024/07/31 00:42:18 by mbriand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isspace(int c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

static long	ft_handle_sign(const char *sign, long nbr)
{
	if (*sign == '-')
		nbr *= -1;
	return (nbr);
}

long	ft_atol(const char *s)
{
	long		nbr;
	const char	*sign;
	int			digit;	

	nbr = 0;
	while (ft_isspace(*s) == 1)
		s++;
	sign = s;
	if (*s == '-' || *s == '+')
		s++;
	while (*s)
	{
		digit = *s - '0';
		if ((((LONG_MAX / 10 == nbr) && digit > LONG_MAX % 10)
				|| (LONG_MAX / 10 < nbr)) && *sign != '-')
			return (LONG_MAX);
		if ((((LONG_MIN / 10 == -nbr) && - digit < LONG_MIN % 10)
				|| (LONG_MIN / 10 > -nbr)) && *sign == '-')
			return (LONG_MIN);
		nbr *= 10;
		nbr += (*s) - 48;
		s++;
	}
	nbr = ft_handle_sign(sign, nbr);
	return (nbr);
}
