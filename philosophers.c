#include "philosophers.h"

unsigned int timestamp(struct timeval tv1, struct timeval tv2)
{
	return ((((tv1.tv_sec * 1000) + (tv1.tv_usec / 1000))) - ((tv2.tv_sec * 1000) + (tv2.tv_usec / 1000)));
}

void	msleep(int value)
{
	usleep(value*1000);
}

int		is_ded(t_id *id, unsigned int eaten)
{
	struct timeval timenow;

	gettimeofday(&timenow, NULL);
	if (id->info->ded == 1)
		return (0);
	if (eaten >= (unsigned int)id->info->ttd)
		{
			printf("%u %d died\n", timestamp(timenow, id->info->timestart), id->id+1);
			id->info->ded = 1;
			return (0);
		}
	return (1);
}

void	pick_fork(t_id *id, int pos)
{
	pthread_mutex_lock(&(id->mutexes[pos]));
	id->info->forks[pos] = 0;
}

void	fork_msg(t_id *id, int pos, int act)
{
	struct timeval	timenow;

	gettimeofday(&timenow, NULL);
	if (act == 1)
	{
		if (id->id == pos)
			printf("%u %d has taken a fork\n",  timestamp(timenow, id->info->timestart), id->id+1);
		else
			printf("%u %d has taken a fork\n",  timestamp(timenow, id->info->timestart), id->id+1);
	}
	else
	{
		if (id->id == pos)
			printf("%u %d has put down a fork\n",  timestamp(timenow, id->info->timestart), id->id+1);
		else
			printf("%u %d has put down a fork\n",  timestamp(timenow, id->info->timestart), id->id+1);
	}
}

void	put_fork(t_id *id, int pos)
{
	pthread_mutex_unlock(&(id->mutexes[pos]));
	id->info->forks[pos] = 1;
}

void	eat_last(t_id *id)
{
	struct timeval timenow;
	gettimeofday(&timenow, NULL);
	pick_fork(id, id->id);
	fork_msg(id, id->id, 1);
	gettimeofday(&timenow, NULL);
	pick_fork(id, 0);
	fork_msg(id, 0, 1);
	gettimeofday(&timenow, NULL);
	printf("%u %d is eating\n",timestamp(timenow, id->info->timestart), id->id+1);
	msleep(id->info->tte);
	put_fork(id, id->id);
	fork_msg(id, id->id, 0);
	put_fork(id, 0);
	fork_msg(id, 0, 0);
}

void	eat(t_id *id)
{
	struct timeval timenow;

	gettimeofday(&timenow, NULL);
	pick_fork(id, id->id);
	fork_msg(id, id->id, 1);
	gettimeofday(&timenow, NULL);
	pick_fork(id, id->id+1);
	fork_msg(id, id->id+1, 1);
	gettimeofday(&timenow, NULL);
	printf("%u %d is eating\n", timestamp(timenow, id->info->timestart), id->id+1);
	msleep(id->info->tte);
	put_fork(id, id->id);
	fork_msg(id, id->id, 0);
	put_fork(id, id->id+1);
	fork_msg(id, id->id+1, 0);

}

void	*routine(void *phil_id)
{
	t_id	*id = (t_id*)phil_id;
	struct timeval	timenow;
	struct timeval	last_eat;
	int				time_eaten;
	int flag = 1;

	time_eaten = 0;
	gettimeofday(&timenow, NULL);
	gettimeofday(&last_eat, NULL);
	while (!id->info->ded)
	{
		gettimeofday(&timenow, NULL);
		if (!is_ded(id, timestamp(timenow, last_eat)))
			return (NULL);
		if (id->id % 2 == 0 && flag)
		{
			gettimeofday(&timenow, NULL);
			printf("%u %d is sleeping\n", timestamp(timenow, id->info->timestart), id->id+1);
			msleep(id->info->tts);
			flag = 0;
		}
		gettimeofday(&timenow, NULL);
		if (!is_ded(id, timestamp(timenow, last_eat)))
			return (NULL);
		if (id->id == (id->info->phil_n - 1))
			eat_last(id);
		else
			eat(id);
		gettimeofday(&last_eat, NULL);
		time_eaten++;
		gettimeofday(&timenow, NULL);
		printf("%u %d is sleeping\n", timestamp(timenow, id->info->timestart), id->id+1);
		msleep(id->info->tts);
		gettimeofday(&timenow, NULL);
		if (!is_ded(id, timestamp(timenow, last_eat)))
			return (NULL);
		printf("%u %d is thinking\n", timestamp(timenow, id->info->timestart), id->id+1);
		msleep(2*id->info->tte - id->info->tts);
		gettimeofday(&timenow, NULL);
		if (!is_ded(id, timestamp(timenow, last_eat)))
			return (NULL);
		gettimeofday(&timenow, NULL);
		if (time_eaten == id->info->number_eat)
			return (NULL);
		if (!is_ded(id, timestamp(timenow, last_eat)))
			return (NULL);
	}
	return (NULL);
}

void	get_values(int	argc, char **argv, t_info *phil_info)
{
	phil_info->phil_n = (int)long_atoi(argv[1]);
	phil_info->ttd = long_atoi(argv[2]);
	phil_info->tte = long_atoi(argv[3]);
	phil_info->tts = long_atoi(argv[4]);
	if (phil_info->phil_n < 1)
		error_msg(2);
	if (phil_info->ttd < 0)
		error_msg(2);
	if (phil_info->tte < 0)
		error_msg(2);
	if (phil_info->tts < 0)
		error_msg(2);
	if (argc == 6)
	{
		phil_info->number_eat = (int)long_atoi(argv[5]);
		if (phil_info->number_eat < 0)
			error_msg(2);
	}
	else
		phil_info->number_eat = -1;
}

void	one_philo(t_info id)
{
	msleep(id.ttd);
	printf("%u 1 has died\n", id.ttd);
	exit(0);
}

int	main(int argc, char **argv)
{
	// int argc = 6;
	// char *argv[6] = {"0", "8", "310", "200", "100", "-1"};

	t_info			phil_info;
	int				i;
	t_id			*phil_id;

	if (argc != 5 && argc != 6)
		error_msg(1);
	get_values(argc, argv, &phil_info);
	i = 0;
	if (phil_info.phil_n == 1)
		one_philo(phil_info);
	gettimeofday(&phil_info.timestart, NULL);
	pthread_t		*phil = malloc(phil_info.phil_n * sizeof(pthread_t));
	pthread_mutex_t *mutexes = malloc(phil_info.phil_n * sizeof(pthread_mutex_t));
	phil_info.forks = malloc(phil_info.phil_n * sizeof(int));
	phil_id = malloc(phil_info.phil_n * sizeof(t_id));
	phil_info.ded = 0;
	while (i < phil_info.phil_n)
	{
		pthread_mutex_init(&mutexes[i], NULL);
		phil_info.forks[i] = 1;
		phil_id[i].info = &phil_info;
		phil_id[i].id = i;
		phil_id[i].mutexes = mutexes;
		i++;
	}
	i = 0;
	while (i < phil_info.phil_n)
	{
		if (pthread_create(phil + i, NULL, &routine, &phil_id[i]))
			return (0);
		i++;
	}
	i = 0;
	while (i < phil_info.phil_n)
	{
		pthread_join(phil[i], NULL);
		i++;
	}
	i = 0;
	while (i < phil_info.phil_n)
	{
		pthread_mutex_destroy(&mutexes[i]);
		i++;
	}
	free(phil);
	free(mutexes);
	free(phil_id);
	free(phil_info.forks);
}
