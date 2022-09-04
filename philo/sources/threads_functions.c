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
	philo->current_time = ft_get_current_time(philo->data);
	ft_msg_fork(list);
	while (second_fork == 0)
	{
		if (philo->philo_nb % 2 == 0)
			second_fork = ft_check_fork(list->next);
		else
			second_fork = ft_check_fork(list);
	}
	philo->current_time = ft_get_current_time(philo->data);
	ft_msg_fork(list);
	ft_eat(philo);
	ft_release_forks(list);
	ft_sleep(philo);
	return (-1);
}

void	ft_sleep(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->is_writing));
	printf("%ld #%i has started to sleep\n", ft_get_current_time(philo->data),
		philo->philo_nb);
	pthread_mutex_unlock(&(philo->data->is_writing));
	usleep(philo->data->time_to_sleep * 1000);
	pthread_mutex_lock(&(philo->data->is_writing));
	printf("%ld #%i has started to think\n", ft_get_current_time(philo->data),
		philo->philo_nb);
	pthread_mutex_unlock(&(philo->data->is_writing));
}

void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->is_writing));
	printf("%ld #%i has started to eat\n", ft_get_current_time(philo->data),
		philo->philo_nb);
	pthread_mutex_unlock(&(philo->data->is_writing));
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
		printf("My current time is %ld\n", ft_get_current_time(philo->data));
		pthread_mutex_unlock(&(philo->data->is_writing));
	}
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
