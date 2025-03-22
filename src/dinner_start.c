/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_start.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 16:23:25 by sbenitez          #+#    #+#             */
/*   Updated: 2025/03/22 14:03:19 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_destroy_mutex(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->n_philos)
		pthread_mutex_destroy(&table->forks[i]);
	pthread_mutex_destroy(&table->eat_lock);
	pthread_mutex_destroy(&table->write_lock);
	pthread_mutex_destroy(&table->dead_lock);
}

void	ft_dinner_start(t_table *t)
{
	pthread_t	monitor;
	int			i;

	i = -1;
	if (pthread_create(&monitor, NULL, &ft_mt_routine, t) != 0)
		return ;
	while (++i < t->n_philos)
	{
		if (pthread_create(&t->philos[i]->th_id, NULL, &ft_ph_ro, t->philos[i]))
			return ;
	}
	i = -1;
	if (pthread_join(monitor, NULL) != 0)
		return ;
	while (++i < t->n_philos)
	{
		if (pthread_join(t->philos[i]->th_id, NULL) != 0)
			return ;
	}
	ft_destroy_mutex(t);
}
