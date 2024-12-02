#include "philo.h"

/* static void	meals(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->lock_meal);
	philo_write("Is eating", philo);
	philo->last_meal = get_current_time();
	philo->meals++;
	ft_usleep(philo->tt_eat);
	pthread_mutex_unlock(&philo->data->lock_meal);
} */

static void	rutine(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	philo_write("has taken a fork r", philo);
	if (philo->data->n_philo == 1)
	{
		ft_usleep(philo->tt_die);
		pthread_mutex_unlock(philo->r_fork);
		return ;
	}
	pthread_mutex_lock(philo->l_fork);
	philo_write("has taken a fork l", philo);
	printf("si %i\n", philo->data->n_philo);
	//pthread_mutex_unlock(&philo->data->lock_meal);

	pthread_mutex_lock(&philo->data->lock_meal);
	philo_write("Is eating", philo);
	philo->last_meal = get_current_time();
	philo->meals++;
	ft_usleep(philo->tt_eat);
	pthread_mutex_unlock(&philo->data->lock_meal);
	//meals(philo);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	philo_write("is sleeping", philo);
	ft_usleep(philo->tt_sleep);
	philo_write("is thinking", philo);
}

void	*philo_daily(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(10);
	while (philo->data->dead_flag == false)
	{
		rutine(philo);
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

void	pthreads(t_philo *philos)
{
	int i;

	i = 0;
	//printf("hola\n");
	printf("n_philo: %i\n", philos->data->n_philo);
	pthread_create(&philos->data->monitoring, NULL, &monitoring, &philos);
	while (i < philos->data->n_philo)
	{
		if (pthread_create(&philos[i].thread, NULL, &philo_daily, &philos[i]) == 0)
			rm_mutex(philos);
		i++;
	}
	i = 0;
	printf("1\n");
	pthread_join(philos->data->monitoring, NULL);
	while (i < philos->data->n_philo)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
}
