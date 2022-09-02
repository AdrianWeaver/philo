/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <aweaver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 10:50:38 by aweaver           #+#    #+#             */
/*   Updated: 2022/09/01 17:57:39 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int	ft_core_program(t_data *data)
{
	long int				start;
	long int				current_time;
	int						i;

	i = 0;
	if (ft_secure_gettime_ms(&start) == -1)
		return (-1);
	while (i < 1)
		i++;
	if (ft_secure_gettime_ms(&current_time) == -1)
		return (-1);
	printf("start = %ld\n", start);
	printf("current = %ld\n", current_time);
	printf("time_spent = %ld\n", current_time - start);
	(void)data;
	return (0);
}

int	ft_check_args(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc != 6)
	{
		write(2, "Please provide the following arguments:\n", 41);
		write(2, "number_of_philosophers, time_to_die, time_to_eat, ", 51);
		write(2, "time_to_sleep, number_of_times_each_philosopher_must_eat\n",
			58);
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
		return (1);
	if (ft_create_structure(&data, argv) == -1)
		return (2);
	if (ft_create_philo_list(&data, &list) == -1)
		return (3);
	if (ft_create_threads(&list) == -1)
		return (4);
	if (ft_core_program(data) == 1)
		return (5);
	printf("Exited everything went ok\n");
	return (0);
}
