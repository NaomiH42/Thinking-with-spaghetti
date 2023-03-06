#include <sys/time.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void	*routine(void *time)
{
	struct timeval	timenow;
	struct timeval	time;
	int	ded;

	ded = 0;
	while (!ded)
	{
		gettimeofday(&timenow, NULL);
		if ((timenow.tv_usec - (*struct)time.tv_usec) > 500)
			ded = 1;
	}
	gettimeofday(&timenow, NULL);
}

int	main(void)
{
	pthread_t		phil;
	int				num_of_phi;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	struct timeval	time;

	long			timestart;

	gettimeofday(&time, NULL);
	pthread_create(&phil, NULL, &routine, &time);
	pthread_join(phil, NULL);
}
