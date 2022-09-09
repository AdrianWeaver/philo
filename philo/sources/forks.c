/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <aweaver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 09:08:20 by aweaver           #+#    #+#             */
/*   Updated: 2022/09/09 09:09:12 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_release_forks(t_list *list)
{
	t_philo	*philo;

	philo = (t_philo *)list->content;
	pthread_mutex_lock(&(philo->m_fork));
	philo->fork = 0;
	pthread_mutex_unlock(&(philo->m_fork));
	philo = (t_philo *)list->next->content;
	pthread_mutex_lock(&(philo->m_fork));
	philo->fork = 0;
	pthread_mutex_unlock(&(philo->m_fork));
	return (0);
}

int	ft_check_fork(t_list *list)
{
	t_philo	*philo;

	philo = (t_philo *)list->content;
	pthread_mutex_lock(&(philo->m_fork));
	if (philo->fork == 0)
	{
		philo->fork = 1;
		return (pthread_mutex_unlock(&(philo->m_fork)), 1);
	}
	pthread_mutex_unlock(&(philo->m_fork));
	return (0);
}

int	ft_take_forks(t_list	*list)
{
	t_philo	*philo;
	int		first_fork;
	int		second_fork;

	first_fork = 0;
	second_fork = 0;
	philo = (t_philo *)list->content;
	while (first_fork == 0)
	{
		if (philo->philo_nb % 2 == 0)
			first_fork = ft_check_fork(list);
		else
			first_fork = ft_check_fork(list->next);
	}
	if (ft_get_current_time(philo->data, &philo->current_time) == 1)
		return (1);
	ft_print_msg(philo, "has taken a fork");
	while (second_fork == 0)
	{
		if (philo->philo_nb % 2 == 0)
			second_fork = ft_check_fork(list->next);
		else
			second_fork = ft_check_fork(list);
	}
	if (ft_get_current_time(philo->data, &philo->current_time) == 1)
		return (1);
	ft_print_msg(philo, "has taken a fork");
	ft_eat(philo);
	ft_release_forks(list);
	ft_sleep(philo);
	return (-1);
}
