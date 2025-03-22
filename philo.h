/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 18:31:59 by gmontoro          #+#    #+#             */
/*   Updated: 2025/03/22 14:11:14 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# define YELLOW "\033[0;93m"
# define BLUE "\033[0;96m"
# define GREEN "\033[0;32m"
# define ORANGE "\033[0;33m"
# define RED "\033[0;31m"
# define WHITE "\033[37;1m"
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <limits.h>
# include <time.h>

typedef pthread_mutex_t	t_mtx;

typedef struct s_philo
{
	int			n_philos;
	int			id;
	long		ttdie;
	long		tteat;
	long		ttsleep;
	size_t		meal_start;
	long		last_meal;
	long		max_meals;
	long		meals_eaten;
	int			*end;
	pthread_t	th_id;
	t_mtx		*write_lock;
	t_mtx		*dead_lock;
	t_mtx		*eat_lock;
	t_mtx		*l_fork;
	t_mtx		*r_fork;
}	t_philo;

typedef struct s_table
{
	int			n_philos;
	long		ttdie;
	long		tteat;
	long		ttsleep;
	long		max_meals;
	long		meal_start;
	int			end;
	t_mtx		write_lock;
	t_mtx		dead_lock;
	t_mtx		eat_lock;
	//mutex
	t_mtx		*forks;
	t_philo		**philos;
}	t_table;

//check_args.c
void	ft_exit_error(char *error);
long	ft_atol(const char *str);
int		ft_check_int(char **av);
long	*ft_parse_args(int ac, char **av);

//data_init.c
void	assign_forks(t_philo *philo, t_mtx *forks, int philo_pos);
void	philo_init(t_table *table);
void	ft_data_init(t_table *table, long *args);

//utils.c
size_t	ft_get_time(void);
void	ft_usleep(int usec);
void	print_action(char *str, t_philo *philo, char *color);
void	print_philo(t_table *t);
void	ft_clean(t_table *table);

//dinner_start.c
void	ft_dinner_start(t_table *table);
void	ft_destroy_mutex(t_table *table);

//eat_sleep_think.c
void	ft_think(t_philo *philo);
void	ft_sleep(t_philo *philo);
void	ft_lock_forks(t_philo *philo);
void	ft_eat(t_philo *philo);

//monitor_routine.c
int		ft_is_everyone_alive(t_table *table);
int		ft_everyone_eated(t_table *table);
void	*ft_mt_routine(void	*args);

//philo_routine.c
void	*ft_ph_ro(void *args);
int		ft_check_alive(t_philo *philo);

#endif