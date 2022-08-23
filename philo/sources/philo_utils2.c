/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <aweaver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 11:43:21 by aweaver           #+#    #+#             */
/*   Updated: 2022/08/05 11:43:21 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*dest_c;
	char	*src_c;

	if (dest == 0 && src == 0 && n > 0)
		return (0);
	dest_c = (char *)dest;
	src_c = (char *)src;
	while (n--)
		*dest_c++ = *src_c++;
	return (dest);
}

static int	ft_is_whitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r')
		return (1);
	return (0);
}

int	ft_atoi(const char *nptr)
{
	int	sign;
	int	nb;

	sign = 1;
	nb = 0;
	while (ft_is_whitespace(*nptr) == 1)
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = -sign;
		nptr++;
	}
	while (ft_isdigit(*nptr))
	{
		nb = (nb * 10) + (*nptr - '0');
		nptr++;
	}
	return (sign * nb);
}
