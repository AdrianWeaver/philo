/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <aweaver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 10:50:38 by aweaver           #+#    #+#             */
/*   Updated: 2022/08/05 10:50:38 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>
#include <stdio.h>
#include <pthread.h>

int	ft_create_structure(t_philo *data, char **argv)
{
	data->number_of_philosophers = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	if (data->number_of_philosophers <= 0 || data->time_to_die <= 0
		|| data->time_to_eat <= 0 || data->time_to_sleep <= 0
		|| data->number_of_times_each_philosopher_must_eat <= 0)
	{
		write(2, "Please provide positive values only\n", 36);
		return (-1);
	}
	if (data->number_of_philosophers == 1)
	{
		write(2, "Why so sadistic?!\n", 18);
		return (-1);
	}
	return (0);
}

int	ft_secure_gettime_ms(long int *time)
{
	struct timeval	t_timeval;

	if (gettimeofday(&t_timeval, NULL) == -1)
	{
		write(2, "gettimeofday failed\n", 21);
		return (1);
	}
	*time = t_timeval.tv_usec;
	return (0);
}

int	ft_core_program(t_philo *data)
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
	//pthread_create();
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
	t_philo	data;

	if (ft_check_args(argc, argv) == -1)
		return (1);
	if (ft_create_structure(&data, argv) == -1)
		return (1);
	if (ft_core_program(&data) == 1)
		return (1);
	return (0);
}
