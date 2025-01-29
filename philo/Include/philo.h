/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anblanco <anblanco@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:14:15 by anblanco          #+#    #+#             */
/*   Updated: 2025/01/21 14:49:55 by anblanco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# define PHILO_H

# include <pthread.h> // biblioteca manejo de hilos 
# include <stdio.h> // printf
# include <stdbool.h> // booleans
# include <sys/time.h> // time
# include <unistd.h>

# define MAX_PHILOS 200

typedef struct data
{
	int				dead_flag;
	int				n_philo;
	int				nes_meals;
	size_t			start;

	pthread_mutex_t	lock_dead;
	pthread_mutex_t	lock_meal;
	pthread_mutex_t	lock_think;
	pthread_mutex_t	forks[MAX_PHILOS];
	pthread_t		monitor;
}			t_data;

typedef struct philo
{
	int				id;
	int				meals;
	size_t			start;
	size_t			last_meal;
	size_t			tt_die;
	size_t			tt_eat;
	size_t			tt_sleep;

	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_t		thread;
	t_data			*data;
}			t_philo;

int		ft_atoi(char *str);
void	philo_write(char *str, t_philo *philo);
size_t	get_current_time(void);
void	ft_usleep(size_t milli);
int		arg_check( char **argv);
void	*philo_daily(void *arg);
void	pthreads(t_philo *philos, t_data *data);
void	init_data(t_data *data, char **argv);
void	init_philos(t_data data, t_philo *philos, char **argv);
void	*monitoring(void *arg);
void	rm_mutex(t_philo *philo);

#endif