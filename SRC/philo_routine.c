#include "philo.h"

static void	meals(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->lock_meal);
	philo_write("Is eating", philo);
	philo->last_meal = get_current_time();
	philo->meals++;
	pthread_mutex_unlock(&philo->data->lock_meal);
	ft_usleep(philo->tt_eat);
}

// si solo hay un filo no termina el programa xdd

static void	rutine(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	philo_write("has taken a fork r", philo);
	pthread_mutex_lock(philo->l_fork);
	philo_write("has taken a fork l", philo);
	meals(philo);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	philo_write("is sleeping", philo);
	ft_usleep(philo->tt_sleep);
	philo_write("is thinking", philo);
}

static int	check_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->lock_dead);
	if (philo->data->dead_flag == 1)
	{
		pthread_mutex_unlock(&philo->data->lock_dead);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->lock_dead);
	return (0);
}

void	*philo_daily(void *arg)
{
	t_philo	*philo;
	int i = 0;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(50);
	while (check_dead(philo) != 1)
	{
		rutine(philo);
		i++;
	}
	return (arg);
}

void	rm_mutex(t_philo *philo)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&philo->data->lock_dead);
	pthread_mutex_destroy(&philo->data->lock_meal);
	pthread_mutex_destroy(&philo->data->lock_think);
	while (i < philo->data->n_philo)
	{
		pthread_mutex_destroy(&philo->data->forks[i]);
		i++;
	}
}
