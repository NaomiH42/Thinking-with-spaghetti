#include "philosophers_b.h"

void	fork_msg_b(t_info_b info, int id, int act)
{
	struct timeval	timenow;

	gettimeofday(&timenow, NULL);
	if (act == 1)
	{
		printf("%u %d has taken a fork\n",
			ts(timenow, info.start), id);
	}
	else
	{
		printf("%u %d has put down a fork\n",
			ts(timenow, info.start), id);
	}
}

void	msleep(int value)
{
	usleep(value * 1000);
}

void	sleeping_b(t_info_b info, int id)
{
	struct timeval	timenow;

	gettimeofday(&timenow, NULL);
	printf("%u %d is sleeping\n", ts(timenow, info.start), id);
	msleep(info.tts);
}

void	thinking_b(t_info_b info, int id)
{
	struct timeval	timenow;

	gettimeofday(&timenow, NULL);
	printf("%u %d is thinking\n", ts(timenow, info.start), id);
	msleep(2 * info.tte - info.tts);
}

int	is_ded_b(int id, unsigned int eaten, t_info_b phil_info)
{
	struct timeval	timenow;

	gettimeofday(&timenow, NULL);
	if (eaten >= (unsigned int)phil_info.ttd)
	{
		printf("%u %d died\n", ts(timenow, phil_info.start),
			id);
		return (0);
	}
	return (1);
}
