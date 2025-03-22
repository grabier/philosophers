/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 13:52:43 by sbenitez          #+#    #+#             */
/*   Updated: 2025/03/22 14:10:42 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	main(int ac, char **av)
{
	t_table		*table;
	long		*args;
	long		time;

	if (ac == 5 || ac == 6)
	{
		args = ft_parse_args(ac, av);
		table = malloc(sizeof(t_table));
		ft_data_init(table, args);
		time = table->meal_start;
		printf("time: %lu\n", table->meal_start);
		free(args);
		if (table->max_meals > 0)
			printf("nbr_limit_meals: %ld\n", table->max_meals);
		ft_dinner_start(table);
		ft_clean(table);
	}
	else
		ft_exit_error("Invalid argument number.");
	return (0);
}
