/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utilities.4.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehasalu <ehasalu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 13:57:04 by ehasalu           #+#    #+#             */
/*   Updated: 2023/03/14 19:16:29 by ehasalu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	eat_last(t_id *id, int *t_eat, struct timeval l_eat)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	pick_fork(id, id->id);
	if (gettimeofday(&time, NULL), !is_ded(id, ts(time, l_eat)))
		return (0);
	fork_msg(id, id->id, 1);
	pick_fork(id, 0);
	if (gettimeofday(&time, NULL), !is_ded(id, ts(time, l_eat)))
		return (0);
	fork_msg(id, 0, 1);
	gettimeofday(&time, NULL);
	printf("%u %d is eating\n", ts(time, id->info->start),
		id->id + 1);
	msleep(id->info->tte);
	put_fork(id, id->id);
	if (gettimeofday(&time, NULL), !is_ded(id, ts(time, l_eat)))
		return (0);
	fork_msg(id, id->id, 0);
	put_fork(id, 0);
	if (gettimeofday(&time, NULL), !is_ded(id, ts(time, l_eat)))
		return (0);
	fork_msg(id, 0, 0);
	(*t_eat)++;
	return (1);
}

int	eat(t_id *id, int *t_eat, struct timeval l_eat)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	pick_fork(id, id->id);
	if (gettimeofday(&time, NULL), !is_ded(id, ts(time, l_eat)))
		return (0);
	fork_msg(id, id->id, 1);
	pick_fork(id, id->id + 1);
	if (gettimeofday(&time, NULL), !is_ded(id, ts(time, l_eat)))
		return (0);
	fork_msg(id, id->id + 1, 1);
	gettimeofday(&time, NULL);
	printf("%u %d is eating\n", ts(time, id->info->start),
		id->id + 1);
	msleep(id->info->tte);
	put_fork(id, id->id);
	if (gettimeofday(&time, NULL), !is_ded(id, ts(time, l_eat)))
		return (0);
	fork_msg(id, id->id, 0);
	put_fork(id, id->id + 1);
	if (gettimeofday(&time, NULL), !is_ded(id, ts(time, l_eat)))
		return (0);
	fork_msg(id, id->id + 1, 0);
	(*t_eat)++;
	return (1);
}

void	first_sleep(t_id *id, int *flag, struct timeval *last_eat)
{
	struct timeval	timenow;

	if (*flag)
		gettimeofday(last_eat, NULL);
	if (id->id % 2 == 0 && *flag)
	{
		gettimeofday(&timenow, NULL);
		printf("%u %d is sleeping\n", ts(timenow, id->info->start), id->id + 1);
		msleep(id->info->tts);
	}
	(*flag) = 0;
}

void	*routine(void *phil_id)
{
	t_id			*id;
	struct timeval	time;
	struct timeval	l_eat;
	int				flag;

	id = (t_id *)phil_id;
	flag = 1;
	while (!id->info->ded)
	{
		first_sleep(id, &flag, &l_eat);
		if (gettimeofday(&time, NULL), !is_ded(id, ts(time, l_eat)))
			return (NULL);
		if (id->id == (id->info->phil_n - 1))
			eat_last(id, &id->t_eat, l_eat);
		else
			eat(id, &id->t_eat, l_eat);
		gettimeofday(&l_eat, NULL);
		sleeping(id);
		if (gettimeofday(&time, NULL), !is_ded(id, ts(time, l_eat)))
			return (NULL);
		thinking(id);
		if (id->t_eat == id->info->number_eat || !is_ded(id, ts(time, l_eat)))
			return (NULL);
	}
	return (NULL);
}
