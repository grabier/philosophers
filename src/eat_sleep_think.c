/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_sleep_think.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 14:06:18 by gmontoro          #+#    #+#             */
/*   Updated: 2025/03/22 14:23:21 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_think(t_philo *philo)
{
	print_action("is thinking", philo, BLUE);
	ft_usleep(1);
}

void	ft_sleep(t_philo *philo)
{
	print_action("is sleeping", philo, GREEN);
	ft_usleep(philo->ttsleep);
}

void	ft_lock_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->r_fork);
		if (ft_check_alive(philo))
			print_action("has taken a fork", philo, ORANGE);
		pthread_mutex_lock(philo->l_fork);
		if (ft_check_alive(philo))
			print_action("has taken a fork", philo, ORANGE);
	}
	else
	{
		pthread_mutex_lock(philo->l_fork);
		if (ft_check_alive(philo))
			print_action("has taken a fork", philo, ORANGE);
		pthread_mutex_lock(philo->r_fork);
		if (ft_check_alive(philo))
			print_action("has taken a fork", philo, ORANGE);
	}
}

void	ft_eat(t_philo *philo)
{
	if (philo->n_philos == 1)
	{
		pthread_mutex_lock(philo->l_fork);
		print_action("has taken a fork", philo, ORANGE);
		ft_usleep(philo->tteat);
		pthread_mutex_unlock(philo->l_fork);
		return ;
	}
	ft_lock_forks(philo);
	print_action("is eating", philo, BLUE);
	pthread_mutex_lock(philo->eat_lock);
	philo->last_meal = ft_get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->eat_lock);
	ft_usleep(philo->tteat);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}
