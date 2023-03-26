/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utilities.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehasalu <ehasalu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 13:57:13 by ehasalu           #+#    #+#             */
/*   Updated: 2023/03/26 19:16:23 by ehasalu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	error_msg(int err)
{
	if (err == 1)
		printf("Incorrect number of arguments.\n");
	else
		printf("Invalid argument.\n");
	exit(0);
}

int	long_atoi(const char *nptr)
{
	size_t	i;
	int		m;
	int		res;

	m = 1;
	res = 0;
	i = 0;
	while ((nptr[i] == ' ') || (nptr[i] >= '\t' && nptr[i] <= '\r'))
		i++;
	if (nptr[i] == '-')
	{
		i++;
		m = -1;
	}
	else if (nptr[i] == '+')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		res = (res * 10) + (nptr[i] - '0');
		i++;
	}
	return (res * m);
}

void	one_philo(t_info id)
{
	msleep(id.ttd);
	printf("%u 1 has died\n", id.ttd);
	exit(0);
}

void	free_stuff(pthread_t **phil,
	pthread_mutex_t **mutexes, t_id **phil_id, t_info *phil_info)
{
	free(*phil);
	free(*mutexes);
	free(*phil_id);
	free(phil_info->forks);
}

unsigned int	ts(struct timeval tv1, struct timeval tv2)
{
	return ((((tv1.tv_sec * 1000) + (tv1.tv_usec / 1000)))
		- ((tv2.tv_sec * 1000) + (tv2.tv_usec / 1000)));
}
