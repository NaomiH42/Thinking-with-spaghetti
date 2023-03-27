/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehasalu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 14:36:44 by ehasalu           #+#    #+#             */
/*   Updated: 2023/03/27 14:36:45 by ehasalu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
