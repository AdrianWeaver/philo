/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <aweaver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 11:23:07 by aweaver           #+#    #+#             */
/*   Updated: 2022/08/05 11:23:07 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>

static char	*ft_skip_zeros(char *str, int len, int i)
{
	while (str[i] == '0' && str[i + 1] != '\0')
	{
		ft_memcpy(&str[i], &str[i + 1], ft_strlen_int(&str[i + 1]));
		str[len - 1] = 0;
		len--;
	}
	return (str);
}

int	ft_strlen_int(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	ft_is_int(char *str)
{
	int	i;
	int	len;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	len = ft_strlen_int(str);
	str = ft_skip_zeros(str, len, i);
	len = ft_strlen_int(str);
	while (str[i])
		if (ft_isdigit(str[i++]) == 0)
			return (0);
	if (len < 10)
		return (1);
	if (len > 11)
		return (0);
	if (len == 10)
		if (ft_strcmp("2147483647", str) < 0)
			return (0);
	if (len == 11)
		if ((ft_strcmp("-2147483648", str) < 0)
			|| (str[0] == '+' && ft_strcmp("+2147483647", str) < 0))
			return (0);
	return (1);
}
