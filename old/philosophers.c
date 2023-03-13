/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehasalu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 13:57:04 by ehasalu           #+#    #+#             */
/*   Updated: 2023/03/13 13:57:05 by ehasalu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	eat_last(t_id *id, int *t_eat)
{
	struct timeval	timenow;

	gettimeofday(&timenow, NULL);
	pick_fork(id, id->id);
	fork_msg(id, id->id, 1);
	gettimeofday(&timenow, NULL);
	pick_fork(id, 0);
	fork_msg(id, 0, 1);
	gettimeofday(&timenow, NULL);
	printf("%u %d is eating\n", ts(timenow, id->info->start),
		id->id + 1);
	msleep(id->info->tte);
	put_fork(id, id->id);
	fork_msg(id, id->id, 0);
	put_fork(id, 0);
	fork_msg(id, 0, 0);
	(*t_eat)++;
}

void	eat(t_id *id, int *t_eat)
{
	struct timeval	timenow;

	gettimeofday(&timenow, NULL);
	pick_fork(id, id->id);
	fork_msg(id, id->id, 1);
	gettimeofday(&timenow, NULL);
	pick_fork(id, id->id + 1);
	fork_msg(id, id->id + 1, 1);
	gettimeofday(&timenow, NULL);
	printf("%u %d is eating\n", ts(timenow, id->info->start),
		id->id + 1);
	msleep(id->info->tte);
	put_fork(id, id->id);
	fork_msg(id, id->id, 0);
	put_fork(id, id->id + 1);
	fork_msg(id, id->id + 1, 0);
	(*t_eat)++;
}

void	first_sleep(t_id *id, int *flag)
{
	struct timeval	timenow;

	if (id->id % 2 == 0 && *flag)
	{
		gettimeofday(&timenow, NULL);
		printf("%u %d is sleeping\n", ts(timenow, id->info->start), id->id + 1);
		msleep(id->info->tts);
		(*flag) = 0;
	}
}

void	*routine(void *phil_id)
{
	t_id			*id;
	struct timeval	timenow;
	struct timeval	last_eat;
	int				t_eat;
	int				flag;

	id = (t_id *)phil_id;
	flag = 1;
	t_eat = 0;
	gettimeofday(&last_eat, NULL);
	while (!id->info->ded)
	{
		first_sleep(id, &flag);
		if (gettimeofday(&timenow, NULL), !is_ded(id, ts(timenow, last_eat)))
			return (NULL);
		if (id->id == (id->info->phil_n - 1))
			eat_last(id, &t_eat);
		else
			eat(id, &t_eat);
		gettimeofday(&last_eat, NULL);
		sleeping(id);
		if (gettimeofday(&timenow, NULL), !is_ded(id, ts(timenow, last_eat)))
			return (NULL);
		thinking(id);
		if (t_eat == id->info->number_eat || !is_ded(id, ts(timenow, last_eat)))
			return (NULL);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_info			phil_info;
	int				i;
	t_id			*phil_id;
	pthread_t		*phil;
	pthread_mutex_t	*mutexes;

	get_values(argc, argv, &phil_info);
	i = -1;
	if (phil_info.phil_n == 1)
		one_philo(phil_info);
	memory_init(&phil_info, &phil, &mutexes, &phil_id);
	phil_init(&phil_info, &mutexes, &phil_id);
	while (++i < phil_info.phil_n)
	{
		pthread_mutex_init(&mutexes[i], NULL);
		pthread_create(phil + i, NULL, &routine, &phil_id[i]);
	}
	i = -1;
	while (++i < phil_info.phil_n)
		pthread_join(phil[i], NULL);
	i = -1;
	while (++i < phil_info.phil_n)
		pthread_mutex_destroy(&mutexes[i]);
	free_stuff(&phil, &mutexes, &phil_id, &phil_info);
}
