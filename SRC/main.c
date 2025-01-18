#include "philo.h"

void	pthreads(t_philo *philos, t_data *data)
{
	int i;

	i = 0;
	if (pthread_create(&data->monitor, NULL, &monitoring, philos) != 0)
		rm_mutex(philos);
	while (i < philos->data->n_philo)
	{
		if( pthread_create(&philos[i].thread, NULL, &philo_daily, &philos[i]) != 0)
			rm_mutex(philos);
		i++;
	}
	i = 0;
	if (pthread_join(data->monitor, NULL) != 0)
		rm_mutex(philos);

	while (i < philos->data->n_philo)
	{
		if (pthread_join(philos[i].thread, NULL) != 0)
			rm_mutex(philos);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_data data;
	t_philo philos;

	if ((argc != 5 || argc != 6) && arg_check(argv))
		return (printf("Sintax error\n"), 1);
	init_data(&data, argv);
	if (argc == 6)
		data.nes_meals = ft_atoi(argv[5]);
	init_philos(data, &philos, argv);
	pthreads(&philos, &data);
	rm_mutex(&philos);
	return (0);
}