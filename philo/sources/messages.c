/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <aweaver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 16:03:41 by aweaver           #+#    #+#             */
/*   Updated: 2022/09/02 16:03:41 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <stdio.h>

void	ft_msg_fork(t_list *list)
{
	t_philo	*philo;
	time_t	current;

	philo = list->content;
	current = ft_get_current_time(philo->data);
	pthread_mutex_lock(&(philo->data->is_writing));
	printf("%ld %i has taken a fork\n", current, philo->philo_nb);
	pthread_mutex_unlock(&(philo->data->is_writing));
}
