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
}	t_id;

void	*routine(void *phil_id)
{
	t_id	*id = (t_id*)phil_id;
	struct timeval	timenow;
	struct timeval	last_eat;
	int	ded;

	ded = 0;
	while (!ded)
	{
		if (id->id == (id->info->phil_n - 1))
		{
			if (id->info->forks[id->id] && id->info->forks[0])
			{
				id->info->forks[id->id] = 0;
				id->info->forks[0] = 0;
				printf("Philosopher %d is eating\n", id->id);
				usleep(id->info->tte);
				gettimeofday(&last_eat, NULL);
				id->info->forks[id->id] = 1;
				id->info->forks[0] = 1;
				printf("Philosopher %d is sleeping\n", id->id);
				usleep(id->info->tts);
			}
		}
		else
		{
			if (id->info->forks[id->id] && id->info->forks[id->id - 1])
			{
				id->info->forks[id->id] = 0;
				id->info->forks[0] = 0;
				usleep(id->info->tte);
				printf("Philosopher %d is eating\n", id->id);
				gettimeofday(&last_eat, NULL);
				id->info->forks[id->id] = 1;
				id->info->forks[0] = 1;
				printf("Philosopher %d is sleeping\n", id->id);
				usleep(id->info->tts);
			}
		}
		if (timenow.tv_usec - last_eat.tv_usec > id->info->ttd)
			ded = 1;
	}
	printf("Dude ded");
}

int	main(void)
{
	t_info			phil_info;
	int				i;
	t_id			*phil_id;

	i = 0;
	phil_info.phil_n = 5;
	pthread_t		*phil = malloc(phil_info.phil_n * sizeof(pthread_t));
	phil_info.ttd = 100000000;
	phil_info.tts = 5000000;
	phil_info.tte = 5000000;
	phil_info.forks = malloc(phil_info.phil_n);
	phil_id = malloc(phil_info.phil_n * sizeof(t_id));
	while (i < phil_info.phil_n)
	{
		phil_info.forks[i] = 1;
		phil_id[i].info = &phil_info;
		phil_id[i].id = i;
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
