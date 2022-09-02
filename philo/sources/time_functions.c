/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <aweaver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 18:33:29 by aweaver           #+#    #+#             */
/*   Updated: 2022/09/01 14:45:09 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_get_current_time(const time_t start, time_t time)
{
	return (time - start);
}

int	ft_secure_gettime_ms(long int *time)
{
	struct timeval	t_timeval;

	if (gettimeofday(&t_timeval, NULL) == -1)
	{
		write(2, "gettimeofday failed\n", 21);
		return (1);
	}
	*time = (t_timeval.tv_sec * 1000) + (t_timeval.tv_usec / 1000);
	return (0);
}
