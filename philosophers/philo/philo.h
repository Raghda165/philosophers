/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryagoub <ryagoub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 18:56:56 by ryagoub           #+#    #+#             */
/*   Updated: 2024/04/25 13:55:37 by ryagoub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <limits.h>
# include <stdio.h>
# include <sys/time.h>
# include <time.h>

typedef struct s_data
{
	int				philos_n;
	int				s_time;
	int				d_time;
	int				e_time;
	int				meals_n;
	int				death_flag;
	int				*forks;
	pthread_mutex_t	*f_mutex;
	pthread_mutex_t	print;
	pthread_mutex_t	death;

}	t_data;

typedef struct s_philo
{
	int				left;
	int				id;
	int				right;
	int				meals_count;
	long			eat_time;
	long			eating_time;
	struct timeval	tv_current;
	struct timeval	tv_passed;
	t_data			*g;
	pthread_t		thread;
}t_philo;
int		ft_atoi(const char *str);
int		taking_fork(t_philo *philo);
int		eating(t_philo *philo);
long	timing(struct timeval *tv_current, struct timeval *tv_passed);
void	*routine(void *cur_philo);
void	clean_up(t_data *general, t_philo **philo);
int		ft_usleep(size_t usec, t_philo *philo);
long	timing(struct timeval *tv_current, struct timeval *tv_passed);
int		check_life(t_philo *philo);
void	one_philo_and_odd(t_philo *philo);
int		check_for_errors(void *s);
void	check_errors(char **av, t_data *general);
void	printing_forks(t_philo *philo);
#endif
