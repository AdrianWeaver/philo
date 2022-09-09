/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <aweaver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 18:52:16 by aweaver           #+#    #+#             */
/*   Updated: 2022/09/09 09:45:34 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

int	ft_lstsize(t_list *lst)
{
	t_list	*start;
	size_t	i;

	start = lst;
	i = 0;
	while (lst)
	{
		i++;
		if (lst->next != start)
			lst = lst->next;
		else
			return (i);
	}
	return (i);
}

void	ft_delete_philo(void *arg)
{
	t_philo	*philo;

	if (arg == NULL)
		return ;
	philo = (t_philo *)arg;
	pthread_mutex_destroy(&(philo->m_fork));
	free(philo);
	philo = NULL;
}

void	ft_delete_data(t_data *data)
{
	pthread_mutex_destroy(&(data->is_writing));
	free(data);
	data = NULL;
}
