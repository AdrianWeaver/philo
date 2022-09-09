/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <aweaver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 09:08:20 by aweaver           #+#    #+#             */
/*   Updated: 2022/09/09 11:56:56 by aweaver          ###   ########.fr       */
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

int	ft_check_if_you_are_dead(t_philo *philo)
{
	time_t	current;

	if (ft_secure_gettime_ms(&current) == -1)
		return (-1);
	if (current - philo->last_meal >= philo->data->time_to_die)
	{
		ft_print_msg(philo, "died");
		return (-1);
	}
	return (0);
}

static int	ft_pick_up_a_fork(int fork, t_philo *philo, t_list *list)
{
	if (fork == 0)
	{
		while (fork == 0)
		{
			if (ft_check_if_you_are_dead(philo) == -1)
				return (-1);
			if (philo->philo_nb % 2 == 0)
				fork += ft_check_fork(list);
			else
				fork += ft_check_fork(list->next);
		}
	}
	else if (fork == 1)
	{
		while (fork == 1)
		{
			if (ft_check_if_you_are_dead(philo) == -1)
				return (-1);
			if (philo->philo_nb % 2 == 0)
				fork += ft_check_fork(list->next);
			else
				fork += ft_check_fork(list);
		}
	}
	return (fork);
}

int	ft_take_forks_and_eat(t_list	*list)
{
	t_philo	*philo;
	int		fork_nb;

	fork_nb = 0;
	philo = (t_philo *)list->content;
	fork_nb = ft_pick_up_a_fork(fork_nb, philo, list);
	if (fork_nb == -1)
		return (-1);
	if (ft_print_msg(philo, "has taken a fork") == -1)
		return (-1);
	fork_nb = ft_pick_up_a_fork(fork_nb, philo, list);
	if (fork_nb == -1)
		return (-1);
	if (ft_print_msg(philo, "has taken a fork") == -1)
		return (-1);
	if (ft_eat(philo) == -1)
		return (-1);
	ft_release_forks(list);
	return (0);
}
