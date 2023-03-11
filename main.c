#include "philosophers.h"

double timestamp(struct timeval tv1, struct timeval tv2)
{
	return (((tv1.tv_sec) * 1000 + (tv2.tv_usec) / 1000) - ((tv2.tv_sec) * 1000 + (tv2.tv_usec) / 1000));
}

void	pick_fork(t_id *id, int pos, struct timeval *timestart, struct timeval *timenow)
{
	pthread_mutex_lock(&(id->mutexes[pos]));
	id->info->forks[pos] = 0;

}

void	fork_msg(t_id *id, int pos, struct timeval *timestart, struct timeval *timenow, int act)
{
	gettimeofday(timenow, NULL);
	if (act == 1)
	{
		if (id->id == pos)
			printf("%.f Philosopher %d picked up left fork %d\n",  timestamp(*timenow, *timestart), id->id, pos);
		else
			printf("%.f Philosopher %d picked up right fork %d\n",  timestamp(*timenow, *timestart), id->id, pos);
	}
	else
	{
		if (id->id == pos)
			printf("%.f Philosopher %d put down left fork %d\n",  timestamp(*timenow, *timestart), id->id, pos);
		else
			printf("%.f Philosopher %d put down right fork %d\n",  timestamp(*timenow, *timestart), id->id, pos);
	}
}

void	put_fork(t_id *id, int pos, struct timeval *timestart, struct timeval *timenow)
{
	pthread_mutex_unlock(&(id->mutexes[pos]));
	id->info->forks[pos] = 1;
}

void	eat_last(t_id *id, struct timeval *timestart, struct timeval *timenow, struct timeval *last_eat)
{
	gettimeofday(timenow, NULL);
	pick_fork(id, id->id, timestart, timenow);
	fork_msg(id, id->id, timestart, timenow, 1);
	pick_fork(id, 0, timestart, timenow);
	fork_msg(id, 0, timestart, timenow, 1);
	printf("%.f Philosopher %d is eating\n", timestamp(*timenow, *timestart), id->id);
	usleep(id->info->tte);
	put_fork(id, id->id, timestart, timenow);
	fork_msg(id, id->id, timestart, timenow, 0);
	put_fork(id, 0, timestart, timenow);
	fork_msg(id, 0, timestart, timenow, 0);
	gettimeofday(last_eat, NULL);
}

void	eat(t_id *id, struct timeval *timestart, struct timeval *timenow, struct timeval *last_eat)
{
	gettimeofday(timenow, NULL);
	pick_fork(id, id->id, timestart, timenow);
	fork_msg(id, id->id, timestart, timenow, 1);
	pick_fork(id, id->id+1, timestart, timenow);
	fork_msg(id, id->id+1, timestart, timenow, 1);
	printf("%.f Philosopher %d is eating\n", timestamp(*timenow, *timestart), id->id);
	usleep(id->info->tte);
	put_fork(id, id->id, timestart, timenow);
	fork_msg(id, id->id, timestart, timenow, 0);
	put_fork(id, id->id+1, timestart, timenow);
	fork_msg(id, id->id+1, timestart, timenow, 0);
	gettimeofday(last_eat, NULL);
}

void	*routine(void *phil_id)
{
	t_id	*id = (t_id*)phil_id;
	struct timeval	timestart;
	struct timeval	timenow;
	struct timeval	last_eat;
	int				time_eaten;
	int	ded;

	time_eaten = 0;
	ded = 0;
	gettimeofday(&timestart, NULL);
	gettimeofday(&last_eat, NULL);
	while (!ded)
	{
		if (id->id == (id->info->phil_n - 1))
		{
				// if (id->id % 2 == 0)
				// {
				// 	gettimeofday(&timenow, NULL);
				// 	printf("%f Philosopher %d is sleeping\n", timenow.tv_usec - timestart.tv_usec, id->id);
				// 	usleep(id->info->tts);
				// }
				eat_last(id, &timestart, &timenow, &last_eat);
				time_eaten++;
				gettimeofday(&timenow, NULL);
				printf("%.f Philosopher %d is sleeping\n", timestamp(timenow, timestart), id->id);
				usleep(id->info->tts);
		}
		else
		{
				// if (id->id % 2 == 0)
				// {
				// 	gettimeofday(&timenow, NULL);
				// 	printf("%f Philosopher %d is sleeping\n", timestamp(*timenow, *timestart), id->id);
				// 	usleep(id->info->tts);
				// }
				eat(id, &timestart, &timenow, &last_eat);
				time_eaten++;
				printf("%lu\n", timestart.tv_sec);
				printf("%lu\n", timenow.tv_sec);
				gettimeofday(&timenow, NULL);
				printf("%.f Philosopher %d is sleeping\n", timestamp(timenow, timestart), id->id);
				usleep(id->info->tts);
				printf("%lu\n", timestart.tv_sec);
				printf("%lu\n", timenow.tv_sec);
		}
		gettimeofday(&timenow, NULL);
		if (time_eaten == id->info->number_eat)
			exit(0);
		if (timenow.tv_usec - last_eat.tv_usec >= id->info->ttd)
		{
			printf("%.f Philosopher %d died RIP\n", timestamp(timenow, timestart), id->id);
			ded = 1;
			exit(0);
		}
	}
}

void	get_values(int	argc, char **argv, t_info *phil_info)
{
	phil_info->phil_n = (int)long_atoi(argv[1]);
	phil_info->ttd = long_atoi(argv[2]);
	phil_info->tte = long_atoi(argv[3]);
	phil_info->tts = long_atoi(argv[4]);
	if (argc == 6)
	{
		phil_info->number_eat = (int)long_atoi(argv[5]);
	}
	else
		phil_info->number_eat = -1;
}

int	main(void)//int argc, char **argv)
{
	int argc = 6;
	char *argv[6] = {"0", "4", "800", "200", "200", "2"};

	t_info			phil_info;
	int				i;
	t_id			*phil_id;

	if (argc != 5 && argc != 6)
		error_msg(1);
	get_values(argc, argv, &phil_info);
	i = 0;
	pthread_t		*phil = malloc(phil_info.phil_n * sizeof(pthread_t));
	pthread_mutex_t *mutexes = malloc(phil_info.phil_n * sizeof(pthread_mutex_t));
	phil_info.forks = malloc(phil_info.phil_n);
	phil_id = malloc(phil_info.phil_n * sizeof(t_id));
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
		pthread_create(phil + i, NULL, &routine, &phil_id[i]);
		i++;
	}
	i = 0;
	while (i < phil_info.phil_n)
	{
		pthread_join(phil[i], NULL);
		i++;
	}
}
