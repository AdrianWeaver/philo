/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <aweaver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 08:38:08 by aweaver           #+#    #+#             */
/*   Updated: 2022/09/09 09:11:11 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

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
