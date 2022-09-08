/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <aweaver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 16:03:41 by aweaver           #+#    #+#             */
/*   Updated: 2022/09/08 18:32:50 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <stdio.h>

int	ft_print_msg(t_philo *philo, char *str)
{
	time_t	current;

	if (ft_get_current_time(philo->data, &current) == 1)
		return (1);
	//check if string printed is death.
	//check if someone died in data structure
	//check if meals are done.
	pthread_mutex_lock(&(philo->data->is_writing));
	printf("%ld %i %s\n", current, philo->philo_nb, str);
	pthread_mutex_unlock(&(philo->data->is_writing));
	return (0);
}
