/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <aweaver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 09:10:38 by aweaver           #+#    #+#             */
/*   Updated: 2022/09/09 19:46:19 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

int	ft_think(t_philo *philo)
{
	if (ft_check_if_you_are_dead(philo) == -1)
		return (-1);
	else
		ft_print_msg(philo, "is thinking");
	return (0);
}

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
	if (ft_secure_gettime_ms(&(philo->last_meal)) == -1)
		return (-1);
	philo->meals++;
	if (philo->meals == philo->data->nb_of_times_each_philo_must_eat)
	{
		pthread_mutex_lock(&(philo->data->m_end));
		philo->data->nb_of_philo_with_enough_meals++;
		pthread_mutex_unlock(&(philo->data->m_end));
	}
	usleep(philo->data->time_to_eat * 1000);
	return (0);
}

void	ft_start_timer(time_t start, t_philo *philo)
{
	time_t	current;

	ft_secure_gettime_ms(&current);
	while (current < start)
	{
		usleep(100);
	}
	(void)philo;
}

void	*ft_routine(void *arg)
{
	t_list	*list;
	t_philo	*philo;
	time_t	current;

	list = (t_list *)arg;
	ft_secure_gettime_ms(&current);
	philo = (t_philo *)list->content;
	ft_start_timer(philo->data->start, philo);
	if (philo->philo_nb % 2 == 0)
		usleep ((philo->data->time_to_eat / 2) * 1000);
	usleep ((philo->philo_nb) * 1000);
	while (1)
	{
		if (ft_take_forks_and_eat(list) == -1)
			return (NULL);
		if (ft_sleep(philo) == -1)
			return (NULL);
		if (ft_think(philo) == -1)
			return (NULL);
	}
	return (NULL);
}
