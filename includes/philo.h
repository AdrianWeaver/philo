/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <aweaver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 11:25:48 by aweaver           #+#    #+#             */
/*   Updated: 2022/08/05 11:25:48 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <stddef.h>
# include <unistd.h>

typedef struct s_philo
{
	int	number_of_philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_of_times_each_philosopher_must_eat;
}				t_philo;

int			ft_strlen_int(char *str);
int			ft_isdigit(int c);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_is_int(char *str);
void		*ft_memcpy(void *dest, const void *src, size_t n);
int			ft_atoi(const char *nptr);

#endif
