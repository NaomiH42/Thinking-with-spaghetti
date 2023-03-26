/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehasalu <ehasalu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 13:57:04 by ehasalu           #+#    #+#             */
/*   Updated: 2023/03/26 18:03:00 by ehasalu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_b.h"

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
	// if (id->info->ded == 1)
	// 	return (0);
	if (eaten >= (unsigned int)phil_info.ttd)
	{
		printf("%u %d died\n", ts(timenow, phil_info.start),
			id);
		return (0);
	}
	return (1);
}


int	eat_b(t_info_b info, int *t_eat, struct timeval l_eat, int id, sem_t *sem)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	sem_wait(sem);
	// if (gettimeofday(&time, NULL), !is_ded_b(id, ts(time, l_eat), info))
	// 		exit(0);
	fork_msg_b(info, id, 1);
	sem_wait(sem);
	// if (gettimeofday(&time, NULL), !is_ded_b(id, ts(time, l_eat), info))
	// 		exit(0);
	fork_msg_b(info, id, 1);
	gettimeofday(&time, NULL);
	printf("%u %d is eating\n", ts(time, info.start),
		id);
	msleep(info.tte);
	sem_post(sem);
	//put_fork_b(info);
	// if (gettimeofday(&time, NULL), !is_ded_b(id, ts(time, l_eat), info))
	// 		exit(0);
	fork_msg_b(info, id, 0);
	//put_fork_b(info);
	sem_post(sem);
	// if (gettimeofday(&time, NULL), !is_ded_b(id, ts(time, l_eat), info))
	// 		exit(0);
	fork_msg_b(info, id, 0);
	(*t_eat)++;
	gettimeofday(&l_eat, NULL);
	return (1);
}

void	first_sleep_b(t_info_b info, int *flag, struct timeval *last_eat, int id)
{
	struct timeval	timenow;

	if (*flag)
		gettimeofday(last_eat, NULL);
	if (id % 2 == 0 && *flag)
	{
		gettimeofday(&timenow, NULL);
		printf("%u %d is sleeping\n", ts(timenow, info.start), id);
		msleep(info.tts);
		// (*flag) = 0;
	}
	(*flag) = 0;
}

void	routine_b(t_info_b info, int id)
{
	struct timeval	time;
	struct timeval	l_eat;
	int				flag;
	int				t_eat;
	sem_t			*sem;


	sem = sem_open("/FORKS", 0);
	t_eat = 0;
	flag = 1;
	while (info.ded)
	{
		first_sleep_b(info, &flag, &l_eat, id);
		gettimeofday(&time, NULL);
		if (gettimeofday(&time, NULL), !is_ded_b(id, ts(time, l_eat), info))
			exit(0);
		eat_b(info, &t_eat, l_eat, id, sem);
		gettimeofday(&l_eat, NULL);
		sleeping_b(info, id);
		if (gettimeofday(&time, NULL), !is_ded_b(id, ts(time, l_eat), info))
			exit(0);
		thinking_b(info, id);
		if (t_eat == info.number_eat)
			exit(0);
		if (gettimeofday(&time, NULL), !is_ded_b(id, ts(time, l_eat), info))
			exit(0);
	}
	exit(0);
}

void	forker(int phil_n, t_info_b phil_info)
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

void	one_philo_b(t_info_b id)
{
	msleep(id.ttd);
	printf("%u 1 has died\n", id.ttd);
	exit(0);
}

int	main(int argc, char **argv)
{
	t_info_b	phil_info;
	// int				i;
	//t_id_b			*phil_id;
	// pthread_t		*phil;
	sem_t	*sem;

	phil_info.ded = 1;
	get_values_b(argc, argv, &phil_info);
	gettimeofday(&phil_info.start, NULL);
	if (phil_info.phil_n == 1)
		one_philo_b(phil_info);
	sem = sem_open("/FORKS", O_CREAT, 0644, phil_info.phil_n);
	sem_close(sem);
	forker(phil_info.phil_n, phil_info);
	waitpid(0, NULL, NULL);
	kill(0, SIGQUIT);
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
