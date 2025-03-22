/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 17:21:14 by sbenitez          #+#    #+#             */
/*   Updated: 2025/03/22 14:05:29 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_is_everyone_alive(t_table *table)
{
	int		i;
	long	aux;

	i = -1;
	pthread_mutex_lock(table->philos[0]->eat_lock);
	while (++i < table->n_philos)
	{
		aux = ft_get_time() - table->philos[i]->last_meal;
		if (aux >= table->philos[i]->ttdie)
		{
			print_action("died", table->philos[i], RED);
			pthread_mutex_unlock(table->philos[0]->eat_lock);
			return (0);
		}
	}
	pthread_mutex_unlock(table->philos[0]->eat_lock);
	return (1);
}

int	ft_everyone_eated(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->n_philos)
	{
		pthread_mutex_lock(table->philos[i]->eat_lock);
		if (table->max_meals == -1)
			return (pthread_mutex_unlock(table->philos[i]->eat_lock), 0);
		if (table->philos[i]->meals_eaten < table->max_meals)
		{
			pthread_mutex_unlock(table->philos[i]->eat_lock);
			return (0);
		}
		pthread_mutex_unlock(table->philos[i]->eat_lock);
	}
	return (1);
}

void	*ft_mt_routine(void	*args)
{
	t_table	*table;

	table = (t_table *)args;
	while (1)
	{
		pthread_mutex_lock(&table->dead_lock);
		if (ft_everyone_eated(table) || !ft_is_everyone_alive(table))
			table->end = 1;
		if (table->end)
		{
			pthread_mutex_unlock(&table->dead_lock);
			break ;
		}
		pthread_mutex_unlock(&table->dead_lock);
	}
	return (args);
}
