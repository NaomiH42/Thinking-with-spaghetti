/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utilities2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehasalu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:06:41 by ehasalu           #+#    #+#             */
/*   Updated: 2023/03/13 15:06:41 by ehasalu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	msleep(int value)
{
	usleep(value * 1000);
}

void	fork_msg(t_id *id, int pos, int act)
{
	struct timeval	timenow;

	gettimeofday(&timenow, NULL);
	if (act == 1)
	{
		if (id->id == pos)
			printf("%u %d has taken a fork\n",
				ts(timenow, id->info->start), id->id + 1);
		else
			printf("%u %d has taken a fork\n",
				ts(timenow, id->info->start), id->id + 1);
	}
	else
	{
		if (id->id == pos)
			printf("%u %d has put down a fork\n",
				ts(timenow, id->info->start), id->id + 1);
		else
			printf("%u %d has put down a fork\n",
				ts(timenow, id->info->start), id->id + 1);
	}
}

int	is_ded(t_id *id, unsigned int eaten)
{
	struct timeval	timenow;

	gettimeofday(&timenow, NULL);
	if (id->info->ded == 1)
		return (0);
	if (eaten >= (unsigned int)id->info->ttd)
	{
		printf("%u %d died\n", ts(timenow, id->info->start),
			id->id + 1);
		id->info->ded = 1;
		return (0);
	}
	return (1);
}

void	pick_fork(t_id *id, int pos)
{
	pthread_mutex_lock(&(id->mutexes[pos]));
	id->info->forks[pos] = 0;
}

void	put_fork(t_id *id, int pos)
{
	pthread_mutex_unlock(&(id->mutexes[pos]));
	id->info->forks[pos] = 1;
}
