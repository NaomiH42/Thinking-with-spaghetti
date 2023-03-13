/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utilities3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehasalu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:12:33 by ehasalu           #+#    #+#             */
/*   Updated: 2023/03/13 15:12:34 by ehasalu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	get_values(int argc, char **argv, t_info *phil_info)
{
	if (argc != 5 && argc != 6)
		error_msg(1);
	phil_info->phil_n = (int)long_atoi(argv[1]);
	phil_info->ttd = long_atoi(argv[2]);
	phil_info->tte = long_atoi(argv[3]);
	phil_info->tts = long_atoi(argv[4]);
	if (phil_info->phil_n < 1)
		error_msg(2);
	if (phil_info->ttd < 0)
		error_msg(2);
	if (phil_info->tte < 0)
		error_msg(2);
	if (phil_info->tts < 0)
		error_msg(2);
	if (argc == 6)
	{
		phil_info->number_eat = (int)long_atoi(argv[5]);
		if (phil_info->number_eat < 0)
			error_msg(2);
	}
	else
		phil_info->number_eat = -1;
}

void	phil_init(t_info *phil_info, pthread_mutex_t **mutexes, t_id **phil_id)
{
	int		i;

	i = 0;
	while (i < phil_info->phil_n)
	{
		phil_info->forks[i] = 1;
		(*phil_id)[i].info = phil_info;
		(*phil_id)[i].id = i;
		(*phil_id)[i].mutexes = *mutexes;
		i++;
	}
}

void	memory_init(t_info *phil_info, pthread_t **phil,
		pthread_mutex_t **mutexes, t_id **phil_id)
{
	gettimeofday(&(phil_info->start), NULL);
	*phil = malloc(phil_info->phil_n * sizeof(pthread_t));
	*mutexes = malloc(phil_info->phil_n * sizeof(pthread_mutex_t));
	phil_info->forks = malloc(phil_info->phil_n * sizeof(int));
	*phil_id = malloc(phil_info->phil_n * sizeof(t_id));
	phil_info->ded = 0;
}

void	sleeping(t_id *id)
{
	struct timeval	timenow;

	gettimeofday(&timenow, NULL);
	printf("%u %d is sleeping\n", ts(timenow, id->info->start), id->id + 1);
	msleep(id->info->tts);
}

void	thinking(t_id *id)
{
	struct timeval	timenow;

	gettimeofday(&timenow, NULL);
	printf("%u %d is thinking\n", ts(timenow, id->info->start), id->id + 1);
	msleep(2 * id->info->tte - id->info->tts);
}
