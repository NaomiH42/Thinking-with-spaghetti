#include "philosophers_b.h"

// int	eat_last_b(t_id *id, int *t_eat, struct timeval l_eat)
// {
// 	struct timeval	time;

// 	gettimeofday(&time, NULL);
// 	pick_fork(id, id->id);
// 	if (gettimeofday(&time, NULL), !is_ded_b(id, ts(time, l_eat), phil_info))
// 		return (0);
// 	fork_msg_b(id, id->id, 1);
// 	pick_fork(id, 0);
// 	if (gettimeofday(&time, NULL), !is_ded_b(id, ts(time, l_eat), phil_info))
// 		return (0);
// 	fork_msg_b(id, 0, 1);
// 	gettimeofday(&time, NULL);
// 	printf("%u %d is eating\n", ts(time, id->info->start),
// 		id->id);
// 	msleep(id->info->tte);
// 	put_fork(id, id->id);
// 	if (gettimeofday(&time, NULL), !is_ded_b(id, ts(time, l_eat), phil_info))
// 		return (0);
// 	fork_msg_b(id, id->id, 0);
// 	put_fork(id, 0);
// 	if (gettimeofday(&time, NULL), !is_ded_b(id, ts(time, l_eat), phil_info))
// 		return (0);
// 	fork_msg_b(id, 0, 0);
// 	(*t_eat)++;
// 	return (1);
// }

// void	pick_fork_b(t_info_b info)
// {
// 	sem_wait(info.forks);
// }

// void	put_fork_b(t_info_b info)
// {
// 	sem_post(info.forks);
// }

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
