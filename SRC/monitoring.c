#include "philo.h"

static int	is_full(t_philo *philos)
{
	int	philos_finish;
	int	i;

	philos_finish = 0;
	i = 0;
	while (i < philos->data->n_philo)
	{
		pthread_mutex_lock(&philos->data->lock_meal);
		if (philos[i].meals >= philos->data->nes_meals)
			philos_finish++;
		pthread_mutex_unlock(&philos->data->lock_meal);
		i++;
	}
	if (philos_finish == philos->data->n_philo)
		return (1);
	else
		return (0);

}

static int	is_dead(t_philo philo)
{
	pthread_mutex_lock(&philo.data->lock_meal);
	if (get_current_time() - philo.last_meal >= philo.tt_die)
		return (1);
	pthread_mutex_unlock(&philo.data->lock_meal);
	return (0);
}

static int	philo_dead_finish(t_philo *philos)
{
	int	i;

	i = 0;
	printf("hola\n");
	printf("n %i\n", philos->data->n_philo);
	while (i < philos->data->n_philo)
	{
		pthread_mutex_lock(&philos->data->lock_dead);
		if (is_dead(philos[i]) == 1)
		{
			philos->data->dead_flag = true;
			return (pthread_mutex_unlock(&philos->data->lock_dead), 1);
		}
		pthread_mutex_unlock(&philos->data->lock_dead);
		i++;
	}
	pthread_mutex_lock(&philos->data->lock_dead);
	if (is_full(philos) == 1)
	{
		philos->data->dead_flag = true;
		return (pthread_mutex_unlock(&philos->data->lock_dead), 1);
	}
	else
		return (pthread_mutex_unlock(&philos->data->lock_dead), 0);
}

void	*monitoring(void *arg)
{
	t_philo	*philos;

	philos = arg;
	while (1)
	{
		printf("monitoring\n");
		if (philo_dead_finish(philos) == 1)
			break ;
	}
	return (arg);
}
