/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <aweaver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 09:10:38 by aweaver           #+#    #+#             */
/*   Updated: 2022/09/09 09:11:25 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

void	ft_sleep(t_philo *philo)
{
	ft_print_msg(philo, "is sleeping");
	usleep(philo->data->time_to_sleep * 1000);
	ft_print_msg(philo, "is thinking");
}

void	ft_eat(t_philo *philo)
{
	//verif que personne n'est dead
	ft_print_msg(philo, "is eating");
	usleep(philo->data->time_to_eat * 1000);
	ft_secure_gettime_ms(&(philo->last_meal));
}

void	*ft_routine(void *arg)
{
	t_list	*list;
	t_philo	*philo;
	time_t	current;

	list = (t_list *)arg;
	ft_secure_gettime_ms(&current);
	philo = (t_philo *)list->content;
	while (current < philo->data->start)
		ft_secure_gettime_ms(&current);
	ft_take_forks(list);
	if (DEBUG_ROUTINE)
	{
		philo = (t_philo *)list->content;
		pthread_mutex_lock(&(philo->data->is_writing));
		printf("My id is %ld\n", philo->thread_id);
		pthread_mutex_unlock(&(philo->data->is_writing));
	}
	return (NULL);
}
