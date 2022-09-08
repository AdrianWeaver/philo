/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <aweaver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 18:33:29 by aweaver           #+#    #+#             */
/*   Updated: 2022/09/08 18:30:01 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_get_current_time(const t_data *data, time_t *current)
{
	time_t	now;

	if (ft_secure_gettime_ms(&now) == 1)
		return (1);
	*current = now - data->start;
	return (0);
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
