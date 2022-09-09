/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <aweaver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 10:50:38 by aweaver           #+#    #+#             */
/*   Updated: 2022/09/09 09:32:30 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int	ft_set_time(t_data *data)
{
	if (ft_secure_gettime_ms(&(data->zero_time)) == -1)
		return (-1);
	data->start = data->zero_time + 100;
	return (0);
}

int	ft_check_args(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc != 6)
	{
		write(2, "Please provide the following arguments:\n", 40);
		write(2, "\t- number_of_philosophers\n\t- time_to_die\n", 41);
		write(2, "\t- time_to_eat\n\t- time_to_sleep\n", 32);
		write(2, "\t- number_of_times_each_philosopher_must_eat\n", 45);
		return (-1);
	}
	while (i < argc)
	{
		if (ft_is_int(argv[i]) == 0)
		{
			write(2, "Please provide numeric arguments\n", 34);
			return (-1);
		}
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data		*data;
	t_list		*list;

	list = NULL;
	data = NULL;
	if (ft_check_args(argc, argv) == -1)
		return (0);
	if (ft_create_structure(&data, argv) == -1)
		return (0);
	if (ft_create_philo_list(&data, &list) == -1)
	{
		ft_delete_data(data);
		ft_lstclear(&list, ft_delete_philo);
		return (0);
	}
	if (ft_set_time(data) == -1)
	{
		ft_delete_data(data);
		ft_lstclear(&list, ft_delete_philo);
		return (0);
	}
	ft_create_threads(&list);
	ft_delete_data(data);
	ft_lstclear(&list, ft_delete_philo);
	return (0);
}
