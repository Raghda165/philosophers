/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up_and_time.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryagoub <ryagoub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 02:42:24 by ryagoub           #+#    #+#             */
/*   Updated: 2024/04/25 10:57:43 by ryagoub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	maximum_time(t_philo *philo)
{
	int	i;

	i = 0;
	if (philo -> g->e_time > philo ->g-> s_time)
		i = philo->g->e_time;
	else
		i = philo->g->s_time;
	return (i);
}

void	clean_up(t_data *general, t_philo **philo)
{
	int	j;

	j = 0;
	while (j < general -> philos_n)
	{
		free(philo[j]);
		pthread_mutex_destroy(&general->f_mutex[j]);
		j++;
	}
	pthread_mutex_destroy(&general->death);
	pthread_mutex_destroy(&general->print);
	free(general->f_mutex);
	free(general->forks);
	free(general);
	free(philo);
}

int	ft_usleep(size_t usec, t_philo *philo)
{
	size_t	msec;
	size_t	start;
	int		elapsed;
	int		remaining;

	start = timing(&philo ->tv_current, &philo -> tv_passed);
	msec = usec / 1000;
	while (timing(&philo ->tv_current, &philo ->tv_passed) - start < msec)
	{
		elapsed = timing(&philo ->tv_current, &philo -> tv_passed) - start;
		remaining = msec - elapsed;
		if (remaining >= 1)
		{
			usleep((remaining * 1e3) / (maximum_time(philo) / 8));
			if (check_life(philo) == 1)
				return (1);
		}
		else
		{
			while (timing(&philo ->tv_current,
					&philo -> tv_passed) - start < msec)
					;
		}
	}
	return (0);
}

long	timing(struct timeval *tv_current, struct timeval *tv_passed)
{
	long	result;

	result = 0;
	gettimeofday(tv_current, NULL);
	result = ((*tv_current).tv_sec * 1000 + (*tv_current).tv_usec / 1000)
		- ((*tv_passed).tv_sec * 1000 + (*tv_passed).tv_usec / 1000);
	return (result);
}

void	one_philo_and_odd(t_philo *philo)
{
	if (philo ->id % 2 == 1)
		ft_usleep(1000, philo);
	if (philo->left == philo -> right)
	{
		ft_usleep(philo->g->d_time * 1000, philo);
	}
}
