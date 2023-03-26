/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_b_utilities2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehasalu <ehasalu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 13:57:13 by ehasalu           #+#    #+#             */
/*   Updated: 2023/03/26 18:39:37 by ehasalu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_b.h"

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

unsigned int	ts(struct timeval tv1, struct timeval tv2)
{
	return ((((tv1.tv_sec * 1000) + (tv1.tv_usec / 1000)))
		- ((tv2.tv_sec * 1000) + (tv2.tv_usec / 1000)));
}

void	get_values_b(int argc, char **argv, t_info_b *phil_info)
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

void	one_philo_b(t_info_b id)
{
	msleep(id.ttd);
	printf("%u 1 has died\n", id.ttd);
	exit(0);
}
