/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absela <absela@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 03:59:22 by absela            #+#    #+#             */
/*   Updated: 2022/10/21 09:27:53 by absela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				numb_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	long long		start;
	int				limit;
	int				death;
	int				ea;
	pthread_mutex_t	printt;
}	t_philo;

typedef struct s_phila
{
	t_philo			*popy;
	pthread_mutex_t	left;
	pthread_mutex_t	*right;
	long long		last_eat;
	pthread_t		phil;
	int				id;
	int				nb_r;
}	t_phila;

void		print_error(char *s);
void		ft_usleep(long long time);
int			ft_atoi(const char *str);
int			ft_isdigit(char *str);
int			in_mutex(t_phila *lol);
int			start_p(t_phila *lol, int numb);
int			create_p(t_phila *lol);
void		mark(t_phila *phil, char *str);
long long	timett(void);
void		*routine(void *sep);
int			createp(t_phila *lol);
int			expiry(t_phila *phil);

#endif