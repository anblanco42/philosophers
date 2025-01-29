/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anblanco <anblanco@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 19:40:23 by anblanco          #+#    #+#             */
/*   Updated: 2025/01/20 19:40:24 by anblanco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_data(t_data *data, char **argv)
{
	int	i;

	i = 0;
	data->dead_flag = 0;
	data->nes_meals = -1;
	data->n_philo = ft_atoi(argv[1]);
	pthread_mutex_init(&data->lock_meal, NULL);
	pthread_mutex_init(&data->lock_think, NULL);
	pthread_mutex_init(&data->lock_dead, NULL);
	while (i < data->n_philo)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
}

void	init_philos(t_data data, t_philo *philos, char **argv)
{
	int	i;

	i = 0;
	while (i < data.n_philo)
	{
		philos[i].id = i + 1;
		philos[i].last_meal = get_current_time();
		philos[i].tt_die = ft_atoi(argv[2]);
		philos[i].tt_eat = ft_atoi(argv[3]);
		philos[i].tt_sleep = ft_atoi(argv[4]);
		philos[i].l_fork = &data.forks[i];
		philos[i].start = get_current_time();
		philos[i].data = &data;
		if (i == 0)
			philos[i].r_fork = &data.forks[data.n_philo - 1];
		else
			philos[i].r_fork = &data.forks[i - 1];
		i++;
	}
}
