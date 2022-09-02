/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <aweaver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 08:38:08 by aweaver           #+#    #+#             */
/*   Updated: 2022/09/02 08:38:08 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int	ft_odd_philo(t_list *list)
{
	t_philo *philo;

	philo = (t_philo *)list->content;
	pthread_mutex_lock(&(philo->m_fork));
	if (philo->fork == 0)
	{
		philo->fork = 1;
		return (pthread_mutex_unlock(&(philo->m_fork)), 1);
	}
	pthread_mutex_unlock(&(philo->m_fork));
	(void)philo;
	return (0);
}

int	ft_even_philo(t_list *list)
{
	t_philo *philo;

	philo = (t_philo *)list->content;
	(void)philo;
	return (0);
}

int	ft_take_forks(t_list	*list)
{
	t_philo	*philo;

	philo = (t_philo *)list->content;
	if (philo->philo_nb % 2 == 0)
		ft_even_philo(list);
	else
		ft_odd_philo(list);
	return (-1);
}

void	ft_eat(t_philo *philo)
{
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
	if (DEBUG)
		printf("ROUTINE PHILO NB %i:\n", philo->philo_nb);
	if (list->next && ft_take_forks(list) == 1)
		ft_msg_fork(list);
	pthread_mutex_lock(&(philo->data->is_writing));
	printf("My id is %ld\n", philo->thread_id);
	printf("My current time is %ld\n", (current - philo->data->start));
	printf("routine start = %ld\nroutine curr  = %ld\n",
		philo->data->start, current);
	pthread_mutex_unlock(&(philo->data->is_writing));
	return (NULL);
}

int	ft_join_threads(t_list *list)
{
	int		i;
	t_philo	*philo;

	i = 0;
	while (i < ft_lstsize(list) && list)
	{
		philo = (t_philo *)list->content;
		if (pthread_join(philo->thread_id, NULL) != 0)
			return (-1);
		i++;
		list = list->next;
	}
	return (0);
}

int	ft_create_threads(t_list **list)
{
	int		i;
	int		thread_create;
	t_philo	*philo;
	t_list	*start;

	i = 0;
	start = *list;
	while (i < ft_lstsize(*list))
	{
		philo = (t_philo *)(*list)->content;
		thread_create = pthread_create(&(philo)->thread_id, NULL,
				&ft_routine, *list);
		if (thread_create != 0)
		{
			printf("create = %d\n", thread_create);
			return (-1);
		}
		*list = (*list)->next;
		i++;
	}
	*list = start;
	if (ft_join_threads(start) == -1)
		return (-1);
	return (0);
}
