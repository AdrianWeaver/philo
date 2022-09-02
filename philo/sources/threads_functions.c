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

void	*ft_routine(void *arg)
{
	t_philo	*philo;
	int		err;

	philo = (t_philo *)arg;
	if (DEBUG)
		printf("ROUTINE:\n");
	err = pthread_mutex_lock(&(philo->data->is_writing));
	printf("My id is %ld\n", philo->thread_id);
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
		printf("JOIN THREADS DEBUG: B:\n");
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
	while (*list)
	{
		philo = (t_philo *)(*list)->content;
		printf("create thread: philo = %p\n", philo);
		thread_create = pthread_create(&(philo)->thread_id, NULL,
				&ft_routine, philo);
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
