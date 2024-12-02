#include "philo.h"

int	main(int argc, char **argv)
{
	t_data data;
	t_philo philos;

	if ((argc != 5 || argc != 6) && arg_check(argv))
		return (printf("Sintax error\n"), 1);
	init_data(&data, argv);
	init_philos(&data, &philos, argv);
	pthreads(&philos);
}