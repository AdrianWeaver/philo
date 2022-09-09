/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_init2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <aweaver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 13:00:44 by aweaver           #+#    #+#             */
/*   Updated: 2022/09/09 13:29:40 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <limits.h>

int	ft_init_mutex(t_data *data)
{
	if (pthread_mutex_init(&(data->is_writing), NULL))
		return (-1);
	if (pthread_mutex_init(&(data->m_end), NULL))
		return (pthread_mutex_destroy(&(data->is_writing)), -1);
	return (0);
}

int	ft_init_data(t_data **data, int argc, char **argv)
{
	(*data)->number_of_philosophers = ft_atoi(argv[1]);
	(*data)->time_to_die = ft_atoi(argv[2]);
	(*data)->time_to_eat = ft_atoi(argv[3]);
	(*data)->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		(*data)->nb_of_times_each_philo_must_eat = ft_atoi(argv[5]);
	else
		(*data)->nb_of_times_each_philo_must_eat = INT_MAX;
	(*data)->nb_of_philo_with_enough_meals = 0;
	(*data)->reaper = 0;
	if (ft_secure_gettime_ms(&(*data)->zero_time) == -1)
		return (-1);
	(*data)->start = (*data)->zero_time + 100;
	return (0);
}
