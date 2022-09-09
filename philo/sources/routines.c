/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <aweaver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 09:10:38 by aweaver           #+#    #+#             */
/*   Updated: 2022/09/09 11:17:36 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

int	ft_sleep(t_philo *philo)
{
	time_t	current;
	time_t	death;

	if (ft_print_msg(philo, "is sleeping") == -1)
		return (-1);
	if (ft_secure_gettime_ms(&(current)) == -1)
		return (-1);
	if (current - philo->last_meal + philo->data->time_to_sleep
		> philo->data->time_to_die)
	{
		death = philo->data->time_to_die - (current - philo->last_meal);
		if (death > 0)
			usleep(death * 1000);
		ft_print_msg(philo, "died");
		return (-1);
	}
	else
	{
		usleep(philo->data->time_to_sleep * 1000);
		return (0);
	}
}

int	ft_eat(t_philo *philo)
{
	if (ft_print_msg(philo, "is eating") == -1)
		return (-1);
	usleep(philo->data->time_to_eat * 1000);
	philo->meals++;
	if (philo->meals == philo->data->nb_of_times_each_philo_must_eat)
	{
		pthread_mutex_lock(&(philo->data->m_end));
		philo->data->nb_of_philo_with_enough_meals++;
		pthread_mutex_unlock(&(philo->data->m_end));
	}
	if (ft_secure_gettime_ms(&(philo->last_meal)) == -1)
		return (-1);
	return (0);
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
	while (1)
	{
		if (ft_take_forks_and_eat(list) == -1)
			return (NULL);
		if (ft_sleep(philo) == -1)
			return (NULL);
		if (ft_print_msg(philo, "is thinking") == -1)
			return (NULL);
	}
	return (NULL);
}
