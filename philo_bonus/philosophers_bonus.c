/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehasalu <ehasalu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 13:57:04 by ehasalu           #+#    #+#             */
/*   Updated: 2023/03/26 18:44:18 by ehasalu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_b.h"

int	eat_b(t_info_b info, struct timeval l_eat, int id, sem_t *sem)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	if (gettimeofday(&time, NULL), !is_ded_b(id, ts(time, l_eat), info))
		exit(0);
	sem_wait(sem);
	fork_msg_b(info, id, 1);
	sem_wait(sem);
	fork_msg_b(info, id, 1);
	gettimeofday(&time, NULL);
	printf("%u %d is eating\n", ts(time, info.start), id);
	msleep(info.tte);
	sem_post(sem);
	fork_msg_b(info, id, 0);
	sem_post(sem);
	fork_msg_b(info, id, 0);
	gettimeofday(&l_eat, NULL);
	return (1);
}

void	first_sleep_b(t_info_b info, int *flag,
		struct timeval *last_eat, int id)
{
	struct timeval	timenow;

	if (*flag)
		gettimeofday(last_eat, NULL);
	if (id % 2 == 0 && *flag)
	{
		gettimeofday(&timenow, NULL);
		printf("%u %d is sleeping\n", ts(timenow, info.start), id);
		msleep(info.tts);
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
		eat_b(info, l_eat, id, sem);
		gettimeofday(&l_eat, NULL);
		sleeping_b(info, id);
		if (gettimeofday(&time, NULL), !is_ded_b(id, ts(time, l_eat), info))
			exit(0);
		thinking_b(info, id);
		if (++t_eat == info.number_eat)
			exit(0);
	}
	exit(0);
}

void	forker(int phil_n, t_info_b phil_info)
{
	pid_t	pid;

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
	t_info_b	phil_info;
	int			i;

	i = 0;
	phil_info.ded = 1;
	get_values_b(argc, argv, &phil_info);
	gettimeofday(&phil_info.start, NULL);
	if (phil_info.phil_n == 1)
		one_philo_b(phil_info);
	sem_unlink("/FORKS");
	phil_info.forks = sem_open("/FORKS", O_CREAT | O_EXCL,
			S_IRWXU, phil_info.phil_n);
	forker(phil_info.phil_n, phil_info);
	if (phil_info.number_eat > 0)
	{
		while (i < phil_info.phil_n)
		{
			waitpid(0, NULL, WCONTINUED);
			i++;
		}
	}
	else
		waitpid(0, NULL, WCONTINUED);
	sem_close(phil_info.forks);
	kill(0, SIGKILL);
}
