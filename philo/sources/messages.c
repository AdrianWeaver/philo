/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <aweaver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 16:03:41 by aweaver           #+#    #+#             */
/*   Updated: 2022/09/09 14:00:03 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <stdio.h>

int	ft_print_msg(t_philo *philo, char *str)
{
	time_t	current;

	if (ft_get_current_time(philo->data, &current) == -1)
		return (-1);
	pthread_mutex_lock(&(philo)->data->m_end);
	if (philo->data->nb_of_philo_with_enough_meals
		>= philo->data->number_of_philosophers)
		return (pthread_mutex_unlock(&(philo)->data->m_end), -1);
	pthread_mutex_unlock(&(philo)->data->m_end);
	if (*str == 'd')
	{
		pthread_mutex_lock(&(philo)->data->m_end);
		philo->data->nb_of_philo_with_enough_meals
			= philo->data->number_of_philosophers;
		pthread_mutex_unlock(&(philo)->data->m_end);
	}
	pthread_mutex_lock(&(philo->data->is_writing));
	printf("%ld %i %s\n", current, philo->philo_nb, str);
	pthread_mutex_unlock(&(philo->data->is_writing));
	return (0);
}
