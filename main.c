#include <sys/time.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct	s_info
{
	int	ttd;
	int	tte;
	int	tts;
	int	phil_n;
	int	*forks;
}	t_info;

typedef struct	s_id
{
	t_info *info;
	int	id;
	pthread_mutex_t *mutexes;
}	t_id;

void	eat_last(t_id *id, struct timeval *timestart, struct timeval *timenow, struct timeval *last_eat)
{
	pthread_mutex_lock(&(id->mutexes[id->id]));
	id->info->forks[id->id] = 0;
	printf("%u Philosopher %d picked up right fork\n",  timenow->tv_usec - timestart->tv_usec, id->id);
	pthread_mutex_lock(&(id->mutexes[0]));
	id->info->forks[0] = 0;
	printf("%u Philosopher %d picked up left fork\n",  timenow->tv_usec - timestart->tv_usec, id->id);
	gettimeofday(timenow, NULL);
	printf("%u Philosopher %d is eating\n",  timenow->tv_usec - timestart->tv_usec, id->id);
	usleep(id->info->tte);
	id->info->forks[id->id] = 1;
	pthread_mutex_unlock(&(id->mutexes[id->id]));
	printf("%u Philosopher %d put down right fork\n",  timenow->tv_usec - timestart->tv_usec, id->id);
	id->info->forks[0] = 1;
	pthread_mutex_unlock(&(id->mutexes[0]));
	printf("%u Philosopher %d put down left fork\n",  timenow->tv_usec - timestart->tv_usec, id->id);
	gettimeofday(last_eat, NULL);
}

void	eat(t_id *id, struct timeval *timestart, struct timeval *timenow, struct timeval *last_eat)
{
	pthread_mutex_lock(&(id->mutexes[id->id]));
	id->info->forks[id->id] = 0;
	printf("%u Philosopher %d picked up right fork\n",  timenow->tv_usec - timestart->tv_usec, id->id);
	pthread_mutex_lock(&(id->mutexes[id->id+1]));
	id->info->forks[id->id+1] = 0;
	printf("%u Philosopher %d picked up left fork\n",  timenow->tv_usec - timestart->tv_usec, id->id);
	usleep(id->info->tte);
	gettimeofday(timenow, NULL);
	printf("%u Philosopher %d is eating\n", timenow->tv_usec - timestart->tv_usec, id->id);
	pthread_mutex_unlock(&(id->mutexes[id->id]));
	printf("%u Philosopher %d put down right fork\n",  timenow->tv_usec - timestart->tv_usec, id->id);
	id->info->forks[id->id] = 1;
	pthread_mutex_unlock(&(id->mutexes[id->id+1]));
	printf("%u Philosopher %d put down left fork\n",  timenow->tv_usec - timestart->tv_usec, id->id);
	id->info->forks[id->id+1] = 1;
	gettimeofday(last_eat, NULL);
}

void	*routine(void *phil_id)
{
	t_id	*id = (t_id*)phil_id;
	struct timeval	timestart;
	struct timeval	timenow;
	struct timeval	last_eat;
	int	ded;

	ded = 0;
	gettimeofday(&timestart, NULL);
	gettimeofday(&last_eat, NULL);
	while (!ded)
	{
		if (id->id == (id->info->phil_n - 1))
		{
				if (id->id % 2 == 0)
				{
					gettimeofday(&timenow, NULL);
					printf("%u Philosopher %d is sleeping\n", timenow.tv_usec - timestart.tv_usec, id->id);
					usleep(id->info->tts);
				}
				eat_last(id, &timestart, &timenow, &last_eat);
				gettimeofday(&timenow, NULL);
				printf("%u Philosopher %d is sleeping\n", timenow.tv_usec - timestart.tv_usec, id->id);
				usleep(id->info->tts);
		}
		else
		{
				if (id->id % 2 == 0)
				{
					gettimeofday(&timenow, NULL);
					printf("%u Philosopher %d is sleeping\n", timenow.tv_usec - timestart.tv_usec, id->id);
					usleep(id->info->tts);
				}
				eat(id, &timestart, &timenow, &last_eat);
				gettimeofday(&timenow, NULL);
				printf("%u Philosopher %d is sleeping\n", timenow.tv_usec - timestart.tv_usec, id->id);
				usleep(id->info->tts);
		}
		gettimeofday(&timenow, NULL);
		if (timenow.tv_usec - last_eat.tv_usec > id->info->ttd)
		{
			printf("%u Philosopher %d died RIP\n", timenow.tv_usec - timestart.tv_usec, id->id);
			ded = 1;
			exit(0);
		}
	}
}

int	main(void)
{
	t_info			phil_info;
	int				i;
	t_id			*phil_id;


	i = 0;
	phil_info.phil_n = 4;
	pthread_t		*phil = malloc(phil_info.phil_n * sizeof(pthread_t));
	pthread_mutex_t *mutexes = malloc(phil_info.phil_n * sizeof(pthread_mutex_t));
	phil_info.ttd = 800;
	phil_info.tts = 200;
	phil_info.tte = 200;
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
