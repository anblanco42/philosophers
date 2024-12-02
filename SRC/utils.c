#include "philo.h"

int	arg_check(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (1);
			j++;
		}
		i++;
	}
	if (ft_atoi(argv[1]) < 1 || ft_atoi(argv[1]) > MAX_PHILOS
		|| ft_atoi(argv[2]) <= 0 || ft_atoi(argv[3]) <= 0
		|| ft_atoi(argv[4]) <= 0)
		return (1);
	return (0);
}

int	ft_atoi(char *str)
{
	int	x;
	int	i;
	int	sig;

	i = 0;
	sig = 1;
	x = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if ((str[i] == 43) || (str[i] == 45))
	{
		if (str[i] == 45)
			sig = sig * -1;
		i++;
	}
	while ((str[i] >= 48) && (str[i] <= 57))
	{
		x = ((x * 10) + (str[i] - 48));
		i++;
	}
	return (x * sig);
}

void	ft_usleep(size_t milli)
{
	size_t	init;

	init = get_current_time();
	while ((get_current_time() - init) < milli)
		usleep(500);
}

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		printf("error\n");
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	philo_write(char *str, t_philo *philo)
{
	size_t	time;

	pthread_mutex_lock(&philo->data->lock_think);
	time = get_current_time() - philo->start;
	if (philo->data->dead_flag == 0)
		printf("%zu %d %s\n", time, philo->id, str);
	pthread_mutex_unlock(&philo->data->lock_think);
}