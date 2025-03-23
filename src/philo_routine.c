/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 10:25:23 by gmontoro          #+#    #+#             */
/*   Updated: 2025/03/23 15:44:51 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_check_alive(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->end == 1)
	{
		pthread_mutex_unlock(philo->dead_lock);
		return (0);
	}
	pthread_mutex_unlock(philo->dead_lock);
	return (1);
}

void	*ft_ph_ro(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	if (philo->id % 2 == 0)
		ft_usleep(100);
	while (ft_check_alive(philo))
	{
		ft_eat(philo);
		if (ft_check_alive(philo))
			ft_think(philo);
		if (ft_check_alive(philo))
			ft_sleep(philo);
	}
	return (args);
}
