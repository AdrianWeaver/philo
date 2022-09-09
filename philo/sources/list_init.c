/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <aweaver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 17:42:59 by aweaver           #+#    #+#             */
/*   Updated: 2022/09/09 13:20:01 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "philo.h"
#include <stdio.h>

int	ft_check_data(t_data *data)
{
	if (DEBUG && DEBUG_DATA)
	{
		printf("DATA: nb of philo=%d\n", data->number_of_philosophers);
		printf("DATA: time to die=%d\n", data->time_to_die);
		printf("DATA: time to eat=%d\n", data->time_to_eat);
		printf("DATA: time to sleep=%d\n", data->time_to_sleep);
		printf("DATA: nb of meals needed=%d\n",
			data->nb_of_times_each_philo_must_eat);
		printf("DATA: mutex address=%p\n", &data->is_writing);
	}
	if (DEBUG && DEBUG_DATA_ADDRESS)
	{
		printf("DATA: nb of philo=%p\n", &data->number_of_philosophers);
		printf("DATA: time to die=%p\n", &data->time_to_die);
		printf("DATA: time to eat=%p\n", &data->time_to_eat);
		printf("DATA: time to sleep=%p\n", &data->time_to_sleep);
		printf("DATA: nb of meals needed=%p\n",
			&data->nb_of_times_each_philo_must_eat);
		printf("DATA: mutex address=%p\n", &data->is_writing);
	}
	return (0);
}

int	ft_check_philo(t_list *list)
{
	int		i;
	t_philo	*philo;

	i = 0;
	philo = (t_philo *)list->content;
	while (i < philo->data->number_of_philosophers)
	{
		philo = (t_philo *)list->content;
		if (DEBUG && DEBUG_DATA)
		{
			printf("PHILO:philo nb %d\n", i);
			printf("PHILO:thread_id %ld\n", philo->thread_id);
		}
		i++;
		list = list->next;
	}
	return (0);
}

int	ft_init_philo_list(int i, t_philo *new_philo, t_list *list, t_data *data)
{
	t_list	*last;

	new_philo->data = data;
	new_philo->thread_id = i + 1;
	new_philo->philo_nb = i + 1;
	new_philo->fork = 0;
	new_philo->last_meal = data->zero_time;
	new_philo->meals = 0;
	if (pthread_mutex_init(&(new_philo->m_fork), NULL))
	{
		free(new_philo);
		last = ft_lstlast(list);
		last->next = NULL;
		return (1);
	}
	return (0);
}

int	ft_create_philo_list(t_data **data, t_list **list)
{
	t_list	*new;
	t_philo	*new_philo;
	t_list	*last;
	int		i;

	i = 0;
	while (i < (*data)->number_of_philosophers)
	{
		new_philo = malloc(sizeof(*new_philo) * 1);
		if (new_philo == NULL)
			return (1);
		if (ft_init_philo_list(i, new_philo, *list, *data) == 1)
			return (1);
		new = ft_lstnew((void *)new_philo);
		ft_lstadd_back(list, new);
		i++;
	}
	last = ft_lstlast(*list);
	last->next = *list;
	ft_check_philo(*list);
	return (0);
}

int	ft_create_structure(t_data **data, int argc, char **argv)
{
	*data = malloc(sizeof(**data) * 1);
	if (*data == NULL)
		return (-1);
	if (ft_init_data(data, argc, argv) == -1)
		return (free(*data), -1);
	if ((*data)->number_of_philosophers <= 0 || (*data)->time_to_die <= 0
		|| (*data)->time_to_eat <= 0 || (*data)->time_to_sleep <= 0
		|| (*data)->nb_of_times_each_philo_must_eat <= 0)
	{
		write(2, "Please provide positive values only\n", 36);
		return (free(*data), -1);
	}
	if ((*data)->number_of_philosophers == 1)
		write(2, "Why so sadistic?!\n", 18);
	if (ft_init_mutex(*data) == -1)
		return (free(*data), -1);
	ft_check_data(*data);
	return (0);
}
