/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryagoub <ryagoub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 20:46:04 by ryagoub           #+#    #+#             */
/*   Updated: 2024/04/25 13:55:55 by ryagoub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_life(t_philo *philo)
{
	pthread_mutex_lock(&philo -> g->death);
	if (philo->g->death_flag == 1)
		return (pthread_mutex_unlock(&philo -> g->death), 1);
	pthread_mutex_unlock(&philo -> g->death);
	if (timing(&philo ->tv_current, &philo -> tv_passed)
		- philo->eat_time > philo->g->d_time)
	{
		pthread_mutex_lock(&philo -> g->death);
		if (philo->g->death_flag == 0)
			philo->g->death_flag = 1;
		else
			return (pthread_mutex_unlock(&philo -> g->death), 1);
		pthread_mutex_unlock(&philo -> g->death);
		pthread_mutex_lock(&philo -> g->print);
		printf("%ld %d died\n", timing
			(&philo ->tv_current, &philo -> tv_passed), philo->id);
		pthread_mutex_unlock(&philo -> g->print);
		return (1);
	}
	return (0);
}

void	*routine(void *cur_philo)
{
	t_philo	*philo;

	philo = (t_philo *)cur_philo;
	one_philo_and_odd(philo);
	while (check_life(philo) != 1)
	{
		ft_usleep(1000, philo);
		if (check_life(philo) == 1)
			break ;
		if (philo->g->meals_n != 0 && philo->meals_count == philo->g->meals_n)
			break ;
		if (taking_fork(philo) == 1)
			break ;
	}
	return (0);
}

int	sleeping(t_philo *philo)
{
	if (check_life(philo) == 1)
		return (1);
	pthread_mutex_lock(&philo -> g->print);
	printf("%ld %d is sleeping\n", timing
		(&philo ->tv_current, &philo -> tv_passed), philo->id);
	pthread_mutex_unlock(&philo -> g->print);
	ft_usleep (philo->g->s_time * 1000, philo);
	if (check_life(philo) == 1)
		return (1);
	pthread_mutex_lock(&philo -> g->print);
	printf("%ld %d is thinking\n", timing
		(&philo ->tv_current, &philo -> tv_passed), philo->id);
	pthread_mutex_unlock(&philo -> g->print);
	return (0);
}

int	eating(t_philo *philo)
{
	if (check_life(philo) == 1)
		return (1);
	pthread_mutex_lock(&philo -> g->print);
	printf("%ld %d is eating\n", timing
		(&philo ->tv_current, &philo -> tv_passed), philo->id);
	pthread_mutex_unlock(&philo -> g->print);
	philo->eat_time = timing(&philo ->tv_current, &philo -> tv_passed);
	philo->meals_count++;
	ft_usleep (philo->g->e_time * 1000, philo);
	pthread_mutex_lock(&philo -> g ->f_mutex[philo->left]);
	pthread_mutex_lock(&philo -> g->f_mutex[philo->right]);
	philo->g -> forks[philo->right] = philo->id;
	philo->g -> forks[philo->left] = philo->id;
	pthread_mutex_unlock(&philo -> g->f_mutex[philo->left]);
	pthread_mutex_unlock(&philo -> g->f_mutex[philo->right]);
	if (sleeping(philo) == 1)
		return (1);
	return (0);
}

int	taking_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo -> g->f_mutex[philo->left]);
	pthread_mutex_lock(&philo -> g ->f_mutex[philo->right]);
	if ((philo->g -> forks[philo->right] != -1 && philo->g -> forks
			[philo->left] != -1 && philo->g -> forks[philo->left] != philo->id
			&& philo->g -> forks[philo->right] != philo->id)
		|| (philo->g -> forks [philo->right] == 0
			&& philo->g -> forks[philo->left] == 0))
	{
		philo->g-> forks[philo->right] = -1;
		philo->g -> forks[philo->left] = -1;
		pthread_mutex_unlock(&philo -> g ->f_mutex[philo->left]);
		pthread_mutex_unlock(&philo -> g ->f_mutex[philo->right]);
		if (check_life(philo) == 1)
			return (1);
		printing_forks(philo);
		if (eating(philo) == 1)
			return (1);
		return (0);
	}
	pthread_mutex_unlock(&philo -> g->f_mutex[philo->left]);
	pthread_mutex_unlock(&philo -> g ->f_mutex[philo->right]);
	return (0);
}
