/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehasalu <ehasalu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 13:57:04 by ehasalu           #+#    #+#             */
/*   Updated: 2023/03/14 19:52:46 by ehasalu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	sleeping_b(t_info info, int id)
{
	struct timeval	timenow;

	gettimeofday(&timenow, NULL);
	printf("%u %d is sleeping\n", ts(timenow, info.start), id);
	msleep(info.tts);
}

// void	thinking_b(t_info info, int id)
// {
// 	struct timeval	timenow;

// 	gettimeofday(&timenow, NULL);
// 	printf("%u %d is thinking\n", ts(timenow, info->start), id);
// 	msleep(2 * info->tte - info->tts);
// }


// int	is_ded_b(int id, unsigned int eaten, t_info phil_info)
// {
// 	struct timeval	timenow;

// 	gettimeofday(&timenow, NULL);
// 	// if (id->info->ded == 1)
// 	// 	return (0);
// 	if (eaten >= (unsigned int)phil_info.ttd)
// 	{
// 		printf("%u %d died\n", ts(timenow, phil_info.start),
// 			id->id);
// 		return (0);
// 	}
// 	return (1);
// }

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

void	fork_msg_b(t_info info, int id, int act)
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

int	eat_b(t_info info, int *t_eat, struct timeval l_eat, int id)
{
	struct timeval	time;

	gettimeofday(&time, NULL);

	//pick_fork(id, id->id);
	// if (gettimeofday(&time, NULL), !is_ded_b(id, ts(time, l_eat), phil_info))
	// 	return (0);
	fork_msg_b(info, id, 1);
	//pick_fork(id, id);
	// if (gettimeofday(&time, NULL), !is_ded_b(id, ts(time, l_eat), phil_info))
	// 	return (0);
	fork_msg_b(info, id, 1);
	gettimeofday(&time, NULL);
	printf("%u %d is eating\n", ts(time, info.start),
		id);
	msleep(info.tte);
	//put_fork(id, id);
	// if (gettimeofday(&time, NULL), !is_ded_b(id, ts(time, l_eat), phil_info))
	// 	return (0);
	fork_msg_b(info, id, 0);
	//put_fork(id, id);
	// if (gettimeofday(&time, NULL), !is_ded_b(id, ts(time, l_eat), phil_info))
	// 	return (0);
	fork_msg_b(info, id, 0);
	(*t_eat)++;
	gettimeofday(&l_eat, NULL);
	return (1);
}

void	first_sleep_b(t_info info, int *flag, struct timeval *last_eat, int id)
{
	struct timeval	timenow;

	if (*flag)
		gettimeofday(last_eat, NULL);
	if (id % 2 == 0 && *flag)
	{
		gettimeofday(&timenow, NULL);
		printf("%u %d is sleeping\n", ts(timenow, info.start), id);
		msleep(info.tts);
		(*flag) = 0;
	}
}

void	routine_b(t_info info, int id)
{
	struct timeval	time;
	struct timeval	l_eat;
	int				flag;
	int				t_eat;

	t_eat = 0;
	flag = 1;
	while (info.ded)
	{
		first_sleep_b(info, &flag, &l_eat, id);
		gettimeofday(&time, NULL);
		// if (gettimeofday(&time, NULL), !is_ded_b(id, ts(time, l_eat), phil_info))
		// 	return ;
		eat_b(info, &t_eat, l_eat, id);
		gettimeofday(&l_eat, NULL);
		// sleeping(id);
		// if (gettimeofday(&time, NULL), !is_ded_b(id, ts(time, l_eat), phil_info))
		// 	return ;
		// thinking(id);
		if (t_eat == info.number_eat)
			return ;
		// if (t_eat == phil_info.number_eat || !is_ded_b(id, ts(time, l_eat), phil_info))
		// 	return ;
	}
	return ;
}

void	forker(int phil_n, t_info phil_info)
{
	pid_t pid;

	if (phil_n > 0)
	{
		pid = fork();
		if (pid < 0)
		{
			perror("fork");
		}
		else if (pid == 0)
		{
			routine_b(phil_info, phil_n);
		}
		else if (pid > 0)
			forker (phil_n - 1, phil_info);
	}
}

int	main(int argc, char **argv)
{
	t_info			phil_info;
	// int				i;
	//t_id_b			*phil_id;
	// pthread_t		*phil;

	get_values(argc, argv, &phil_info);
	gettimeofday(&phil_info.start, NULL);
	if (phil_info.phil_n == 1)
		one_philo(phil_info);
	forker(phil_info.phil_n, phil_info);
	// memory_init(&phil_info, &phil, &mutexes, &phil_id);
	// phil_init(&phil_info, &mutexes, &phil_id);
	// while (++i < phil_info.phil_n)
	// {

	// }
	// i = -1;
	// while (++i < phil_info.phil_n)
	// 	pthread_join(phil[i], NULL);
	// i = -1;
	// while (++i < phil_info.phil_n)
	// 	pthread_mutex_destroy(&mutexes[i]);
	// free_stuff(&phil, &mutexes, &phil_id, &phil_info);
}
