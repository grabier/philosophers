/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:17:08 by sbenitez          #+#    #+#             */
/*   Updated: 2025/03/22 14:01:50 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	assign_forks(t_philo *philo, t_mtx *forks, int philo_pos)
{
	if (philo->id == 1)
	{
		philo->l_fork = &forks[(philo_pos)];
		philo->r_fork = &forks[philo->n_philos -1];
	}
	else
	{
		philo->l_fork = &forks[(philo_pos)];
		philo->r_fork = &forks[philo_pos - 1];
	}
}

void	philo_init(t_table *table)
{
	int		i;
	t_philo	**philo;

	i = -1;
	philo = malloc(sizeof(t_philo *) * table->n_philos);
	while (++i < table->n_philos)
	{
		philo[i] = (t_philo *)malloc(sizeof(t_philo));
		philo[i]->n_philos = table->n_philos;
		philo[i]->id = i + 1;
		philo[i]->ttdie = table->ttdie;
		philo[i]->tteat = table->tteat;
		philo[i]->ttsleep = table->ttsleep;
		philo[i]->meal_start = table->meal_start;
		philo[i]->last_meal = ft_get_time();
		philo[i]->max_meals = table->max_meals;
		philo[i]->meals_eaten = 0;
		philo[i]->end = &table->end;
		philo[i]->write_lock = &table->write_lock;
		philo[i]->dead_lock = &table->dead_lock;
		philo[i]->eat_lock = &table->eat_lock;
		assign_forks(philo[i], table->forks, i);
	}
	table->philos = philo;
}

void	ft_data_init(t_table *table, long *args)
{
	int	i;

	i = -1;
	table->n_philos = args[0];
	table->ttdie = args[1];
	table->tteat = args[2];
	table->ttsleep = args[3];
	if (args[4] != -1)
		table->max_meals = args[4];
	else
		table->max_meals = -1;
	table->end = 0;
	table->meal_start = ft_get_time();
	table->forks = malloc(sizeof(t_mtx) * table->n_philos);
	while (++i < table->n_philos)
		pthread_mutex_init(&table->forks[i], NULL);
	pthread_mutex_init(&table->write_lock, NULL);
	pthread_mutex_init(&table->dead_lock, NULL);
	pthread_mutex_init(&table->eat_lock, NULL);
	philo_init(table);
}
