/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryagoub <ryagoub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 19:33:43 by ryagoub           #+#    #+#             */
/*   Updated: 2024/04/25 13:37:06 by ryagoub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	meals_num(char **av, t_data *general)
{
	if (ft_atoi(av[5]) <= 0 || check_for_errors(av[5]) == 0)
	{
		printf("Error\n");
		free(general);
		exit(EXIT_FAILURE);
	}
	general->meals_n = ft_atoi(av[5]);
}

void	define_forks(t_philo **philo, int j)
{
	if (philo[j]->id % 2 == 1)
	{
		philo[j]->left = j;
		philo[j]->right = (j + 1) % philo[j]-> g-> philos_n;
	}
	else
	{
		philo[j]->right = j;
		philo[j]->left = (j + 1) % philo[j]-> g-> philos_n;
	}
}

void	init_general(int ac, char **av, t_data *general)
{
	int	i;

	i = 0;
	check_errors(av, general);
	general->death_flag = 0;
	if (ac == 6)
		meals_num(av, general);
	else
		general->meals_n = 0;
	general->f_mutex = malloc(sizeof(pthread_mutex_t) * general-> philos_n);
	if (!general->f_mutex)
		exit(EXIT_FAILURE);
	general->forks = malloc(sizeof(int) * general->philos_n);
	if (!general->forks)
		exit(EXIT_FAILURE);
	while (i < general->philos_n)
	{
		general->forks[i] = 0;
		if (pthread_mutex_init(&general->f_mutex[i], NULL) != 0)
			exit(EXIT_FAILURE);
		i++;
	}
	if (pthread_mutex_init(&general->print, NULL) != 0
		|| pthread_mutex_init(&general->death, NULL) != 0)
		exit(EXIT_FAILURE);
}

void	make_philo(t_data *general, t_philo **philo)
{
	int	j;

	j = 0;
	while (j < general->philos_n)
	{
		philo[j] = malloc(sizeof(t_philo));
		if (!philo[j])
			exit(EXIT_FAILURE);
		philo[j]-> id = j + 1;
		philo[j]->meals_count = 0;
		philo[j]->eat_time = 0;
		philo[j]->g = general;
		define_forks(philo, j);
		gettimeofday(&philo[j]->tv_passed, NULL);
		philo[j]-> tv_current = philo[j]->tv_passed;
		if (pthread_create(&philo[j]->thread, NULL,
				&routine, (void *)philo[j]) != 0)
			exit(EXIT_FAILURE);
		j++;
	}
}

int	main(int ac, char **av)
{
	t_data	*general;
	t_philo	**philos;
	int		j;

	if (ac == 5 || ac == 6)
	{
		general = malloc(sizeof(t_data));
		init_general(ac, av, general);
		philos = malloc (sizeof(t_philo *) * general -> philos_n);
		make_philo(general, philos);
		j = 0;
		while (j < general->philos_n)
		{
			if (pthread_join(philos[j]-> thread, NULL) != 0)
				return (1);
			j++;
		}
		clean_up(general, philos);
		return (0);
	}
	printf("INVALID NUMBER OF ARGS\n");
	return (1);
}
