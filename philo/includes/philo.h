/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <aweaver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 11:25:48 by aweaver           #+#    #+#             */
/*   Updated: 2022/09/01 17:34:29 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <stddef.h>
# include <unistd.h>
# include <pthread.h>
# include <time.h>

# define T_PHILO "(t_philo *)list->content"
# define DEBUG 1
# define DEBUG_DATA 1
# define DEBUG_DATA_ADDRESS 1

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_data
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	pthread_mutex_t	is_writing;
	time_t			start;
}				t_data;

typedef struct s_philo
{
	pthread_t		thread_id;
	t_data			*data;
	int				fork;
}			t_philo;

int			ft_strlen_int(char *str);
int			ft_isdigit(int c);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_is_int(char *str);
void		*ft_memcpy(void *dest, const void *src, size_t n);
int			ft_atoi(const char *nptr);

void		ft_lstadd_back(t_list **alst, t_list *new);
void		ft_lstclear(t_list **lst, void (*del)(void *));
void		ft_lstdelone(t_list *lst, void (*del)(void *));
int			ft_lstsize(t_list *list);
t_list		*ft_lstnew(void *content);
t_list		*ft_lstlast(t_list *lst);
int			ft_create_philo_list(t_data **data, t_list **list);
int			ft_create_structure(t_data **data, char **argv);

int			ft_get_current_time(const time_t start, time_t time);
int			ft_secure_gettime_ms(long int *time);

//THREAD FUNCTIONS
int			ft_create_threads(t_list **list);
int			ft_join_threads(t_list *list);
void		*ft_routine(void *arg);

#endif
