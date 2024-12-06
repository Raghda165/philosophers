/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryagoub <ryagoub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 14:05:38 by ryagoub           #+#    #+#             */
/*   Updated: 2024/04/25 13:55:24 by ryagoub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_for_errors(void *s)
{
	int		i;
	char	*str;

	str = (char *) s;
	i = 0;
	if (!str || str[0] == '\0')
		return (0);
	else if (str[i] == ' ')
	{
		while (str[i] == ' ')
			i++;
		if (!str[i])
			return (0);
	}
	while (str[i] != '\0')
	{
		if ((str[i] >= '0' && str[i] <= '9') || (str[i] == ' ')
			|| ((str[i] == '-' || str[i] == '+')))
			i++;
		else
			return (0);
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	size_t	i;
	int		sign;
	long	result;

	i = 0;
	sign = 1;
	result = 0;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == ' '))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = sign * -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - '0';
		if ((result * sign) < INT_MIN || (result > INT_MAX && sign == 1))
			return (0);
		i++;
	}
	if (str[i] == '+' || str[i] == '-')
		return (0);
	return (sign * result);
}

void	check_errors(char **av, t_data *general)
{
	int	i;

	i = 1;
	while (i < 5)
	{
		if (check_for_errors((void *)av[i]) == 0)
		{
			printf("Error\n");
			free(general);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	if (ft_atoi(av[1]) > 200 || ft_atoi(av[2]) < 60 || ft_atoi(av[3]) < 60
		|| ft_atoi(av[1]) <= 0 || ft_atoi(av[4]) < 60)
	{
		printf("Error\n");
		free(general);
		exit(EXIT_FAILURE);
	}
	general -> philos_n = ft_atoi(av[1]);
	general->d_time = ft_atoi(av[2]);
	general->e_time = ft_atoi(av[3]);
	general->s_time = ft_atoi(av[4]);
}

void	printing_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo -> g->print);
	printf("%ld %d has taken a fork\n", timing
		(&philo ->tv_current, &philo -> tv_passed), philo->id);
	printf("%ld %d has taken a fork\n", timing
		(&philo ->tv_current, &philo -> tv_passed), philo->id);
	pthread_mutex_unlock(&philo -> g->print);
}
