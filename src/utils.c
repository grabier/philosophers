/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:05:56 by gmontoro          #+#    #+#             */
/*   Updated: 2025/03/22 14:10:46 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_clean(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->n_philos)
		free(table->philos[i]);
	free(table->philos);
	free(table->forks);
	free(table);
}

void	print_philo(t_table *t)
{
	int	i;

	i = 0;
	printf("ttdie: %ld\n", t->ttdie);
	printf("ttsleep: %ld\n", t->ttsleep);
	printf("tteat: %ld\n", t->tteat);
	printf("max_meals: %ld\n", t->max_meals);
	printf("meal_start: %ld\n", t->meal_start);
	while (i < t->n_philos)
	{
		printf("id: %i\n", t->philos[i]->id);
		printf("last meal: %ld\n", t->philos[i]->last_meal);
		printf("meals_eaten: %ld\n", t->philos[i]->meals_eaten);
		printf("meal start: %ld\n", t->philos[i]->meal_start);
		i++;
	}
	return ;
}

void	print_action(char *str, t_philo *philo, char *color)
{
	long	time;

	pthread_mutex_lock(philo->write_lock);
	time = ft_get_time() - philo->meal_start;
	printf("%s[%ld] %d %s\n", color, time, philo->id, str);
	pthread_mutex_unlock(philo->write_lock);
}

size_t	ft_get_time(void)
{
	struct timeval	tv;
	size_t			ret;

	gettimeofday(&tv, NULL);
	ret = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (ret);
}

void	ft_usleep(int ms)
{
	if (usleep(ms * 1000) == -1)
		return ;
}
