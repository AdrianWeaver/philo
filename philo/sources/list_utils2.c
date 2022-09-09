/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <aweaver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 18:52:16 by aweaver           #+#    #+#             */
/*   Updated: 2022/08/25 18:52:16 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
