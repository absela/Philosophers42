/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absela <absela@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 03:59:55 by absela            #+#    #+#             */
/*   Updated: 2022/10/19 01:22:28 by absela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_phila(char **av, t_philo *phil)
{
	phil->numb_philo = ft_atoi(av[1]);
	phil->time_die = ft_atoi(av[2]);
	phil->time_eat = ft_atoi(av[3]);
	phil->time_sleep = ft_atoi(av[4]);
	phil->limit = 0;
	phil->start = timett();
	phil->death = 5;
	if (av[5] != NULL)
	{
		if (ft_atoi(av[5]) < 1)
			return (-1);
	phil->ea = ft_atoi(av[5]);
	}
	else
	{
	phil->limit = 1;
	phil->ea = 0;
	}
	return (1);
}

void	print_error(char *s)
{
	printf("%s\n", s);
}

int	init_phil(char **av, t_philo *phil)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
			if (ft_isdigit(&av[i][j++]) == 0)
				return (print_error("error"), 1);
		i++;
	}
	if (av[1][0] == '\0' || ft_atoi(av[1]) < 0 || ft_atoi(av[2]) < 1
		|| ft_atoi(av[3]) < 1 || ft_atoi(av[4]) < 1)
		return (print_error("error"), 1);
	if (ft_atoi(av[1]) == 0)
		return (1);
	if (init_phila(av, phil) == -1)
		return (print_error("error"), 1);
	return (0);
}

int	main(int ac, char **av)
{
	t_philo	phil;
	t_phila	*lol;
	int		i;

	i = -1;
	if (ac < 5 || ac > 6)
		return (printf("! Erorr arg !"));
	if (init_phil(av, &phil) != 0)
		return (0);
	lol = malloc(sizeof(t_phila) * phil.numb_philo);
	if (!lol)
		return (0);
	while (++i < phil.numb_philo)
		lol[i].popy = &phil;
	createp(lol);
	i = -1;
	expiry(lol);
	while (++i < lol->popy->numb_philo)
		pthread_mutex_destroy(&lol[i].left);
	pthread_mutex_destroy(&lol->popy->printt);
	free(lol);
	return (1);
}
