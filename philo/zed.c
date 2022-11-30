/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zed.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absela <absela@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 03:58:59 by absela            #+#    #+#             */
/*   Updated: 2022/10/21 09:32:21 by absela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	timett(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	mark(t_phila *phil, char *str)
{
	pthread_mutex_lock(&phil->popy->printt);
	if (phil->popy->death == 5)
		printf("%lld %d %s\n", timett() - phil->popy->start, phil->id + 1, str);
	pthread_mutex_unlock(&phil->popy->printt);
}

int	start_p(t_phila *lol, int numb)
{
	int	i;

	i = 0;
	while (i < numb)
	{
		lol[i].last_eat = timett();
		lol[i].id = i;
		if (pthread_create(&lol[i].phil, NULL, &routine, &lol[i]))
			return (0);
		i++;
	}
	return (1);
}

int	in_mutex(t_phila *lol)
{
	int	i;

	i = 0;
	while (i < lol->popy->numb_philo)
	{
		lol[i].nb_r = 0;
		if (pthread_mutex_init(&lol[i].left, NULL) != 0)
			return (1);
		if (i == lol->popy->numb_philo - 1)
			lol[i].right = &lol[0].left;
		else
			lol[i].right = &lol[i + 1].left;
		i++;
	}
	return (0);
}

int	createp(t_phila *lol)
{
	int	numb;

	if (pthread_mutex_init(&lol->popy->printt, NULL) != 0)
		return (0);
	if (in_mutex(lol) != 0)
		return (print_error("error\n"), 1);
	numb = lol->popy->numb_philo;
	if (start_p(lol, numb) == 0)
		return (0);
	return (1);
}
