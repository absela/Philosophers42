/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moko.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absela <absela@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 04:00:05 by absela            #+#    #+#             */
/*   Updated: 2022/10/19 01:32:43 by absela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(long long time)
{
	long long	start;

	start = timett();
	while (timett() < start + time)
		usleep(50);
}

void	*routine(void *sep)
{
	t_phila	*phil;

	phil = sep;
	if ((phil->id + 1) % 2)
		ft_usleep(phil->popy->time_eat);
	while (phil->nb_r < phil->popy->ea || phil->popy->limit)
	{
		pthread_mutex_lock(&phil->left);
		mark(phil, "take fork");
		pthread_mutex_lock(phil->right);
		mark(phil, "take fork");
		mark(phil, "eating");
		phil->nb_r++;
		phil->last_eat = timett();
		ft_usleep(phil->popy->time_eat);
		pthread_mutex_unlock(&phil->left);
		pthread_mutex_unlock(phil->right);
		mark(phil, "sleeping");
		ft_usleep(phil->popy->time_sleep);
		mark(phil, "thinking");
	}
	return (NULL);
}

int	expiry(t_phila *phil)
{
	int			i;
	int			n_eat;
	t_phila		philo;

	while (1)
	{
		i = 0;
		n_eat = 0;
		while (i < phil->popy->numb_philo)
		{
			philo = phil[i];
			if (timett() - philo.last_eat >= phil->popy->time_die)
				return (mark(&philo, "death"), phil->popy->death = 1);
			n_eat += (philo.popy->ea && philo.nb_r == philo.popy->ea);
			i++;
		}
		if (n_eat == philo.popy->numb_philo)
			return (pthread_mutex_lock(&phil->popy->printt));
		usleep(100);
	}
}
