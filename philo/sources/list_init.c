/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <aweaver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 17:42:59 by aweaver           #+#    #+#             */
/*   Updated: 2022/09/01 17:56:35 by aweaver          ###   ########.fr       */
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
			data->number_of_times_each_philosopher_must_eat);
		printf("DATA: mutex address=%p\n", &data->is_writing);
	}
	if (DEBUG && DEBUG_DATA_ADDRESS)
	{
		printf("DATA: nb of philo=%p\n", &data->number_of_philosophers);
		printf("DATA: time to die=%p\n", &data->time_to_die);
		printf("DATA: time to eat=%p\n", &data->time_to_eat);
		printf("DATA: time to sleep=%p\n", &data->time_to_sleep);
		printf("DATA: nb of meals needed=%p\n",
			&data->number_of_times_each_philosopher_must_eat);
		printf("DATA: mutex address=%p\n", &data->is_writing);
	}
	return (0);
}

int	ft_check_philo(t_list *list)
{
	int		i;
	t_philo	*philo;

	i = 0;
	while (list)
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

int	ft_create_philo_list(t_data **data, t_list **list)
{
	t_list	*new;
	t_philo	*new_philo;
	int		i;

	i = 0;
	if (DEBUG)
	{
		printf("CREATE_PHILO_LIST A:\n");
		printf("A:number of philos address = %p\n",
			&(*data)->number_of_philosophers);
		printf("A:number of philos = %d\n", (*data)->number_of_philosophers);
	}
	while (i < (*data)->number_of_philosophers)
	{
		new_philo = malloc(sizeof(*new_philo) * 1);
		if (new_philo == NULL)
			return (-1);
		new_philo->data = *data;
		new_philo->thread_id = i;
		new = ft_lstnew((void *)new_philo);
		ft_lstadd_back(list, new);
		i++;
	}
	ft_check_philo(*list);
	return (0);
}

int	ft_create_structure(t_data **data, char **argv)
{
	*data = malloc(sizeof(**data) * 1);
	(*data)->number_of_philosophers = ft_atoi(argv[1]);
	(*data)->time_to_die = ft_atoi(argv[2]);
	(*data)->time_to_eat = ft_atoi(argv[3]);
	(*data)->time_to_sleep = ft_atoi(argv[4]);
	(*data)->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	if ((*data)->number_of_philosophers <= 0 || (*data)->time_to_die <= 0
		|| (*data)->time_to_eat <= 0 || (*data)->time_to_sleep <= 0
		|| (*data)->number_of_times_each_philosopher_must_eat <= 0)
	{
		write(2, "Please provide positive values only\n", 36);
		return (-1);
	}
	if ((*data)->number_of_philosophers == 1)
	{
		write(2, "Why so sadistic?!\n", 18);
		return (-1);
	}
	if (pthread_mutex_init(&(*data)->is_writing, NULL))
		exit (15);
	ft_check_data(*data);
	ft_secure_gettime_ms(&(*data)->start);
	return (0);
}
