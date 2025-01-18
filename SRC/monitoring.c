#include "philo.h"

static int	is_full(t_philo *philos)
{
	int	philos_finish;
	int	i;

	philos_finish = 0;
	i = 0;
	while (i < philos->data->n_philo && philos->data->nes_meals != -1)
	{
		pthread_mutex_lock(&philos->data->lock_meal);
		if (philos[i].meals >= philos[i].data->nes_meals)
			philos_finish++;
		pthread_mutex_unlock(&philos->data->lock_meal);
		i++;
	}
	if (philos_finish >= philos->data->n_philo)
		return (1);
	else
		return (0);

}

static int	is_dead(t_philo philo)
{
	pthread_mutex_lock(&philo.data->lock_meal);
	if (get_current_time() - philo.last_meal >= philo.tt_die)
	{
		pthread_mutex_unlock(&philo.data->lock_meal);
		return (1);
	}
	pthread_mutex_unlock(&philo.data->lock_meal);
	return (0);
}

static int	philo_dead_finish(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->data->n_philo)
	{
		pthread_mutex_lock(&philos->data->lock_dead);
		if (is_dead(philos[i]) == 1)
		{
			philo_write("Dead", philos);
			philos->data->dead_flag = 1;
			pthread_mutex_unlock(&philos->data->lock_dead);
			return (1);
		}
		pthread_mutex_unlock(&philos->data->lock_dead);
		i++;
	}
	pthread_mutex_lock(&philos->data->lock_dead);
	if (is_full(philos) == 1)
	{
		philos->data->dead_flag = 1;
		pthread_mutex_unlock(&philos->data->lock_dead);
		return (1);
	}
	else
		pthread_mutex_unlock(&philos->data->lock_dead);
	return (0);
}

void	*monitoring(void *arg)
{
	t_philo	*philos;

	philos = arg;
	while (1)
	{
		if (philo_dead_finish(philos) == 1)
			break ;
		ft_usleep(50);
	}
	return (arg);
}
