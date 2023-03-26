/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_b.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehasalu <ehasalu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 13:57:07 by ehasalu           #+#    #+#             */
/*   Updated: 2023/03/26 18:40:26 by ehasalu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_B_H
# define PHILOSOPHERS_B_H

# include <sys/time.h>
# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <semaphore.h>
# include <sys/stat.h>
# include <fcntl.h>

typedef struct s_info_b
{
	int				ttd;
	int				tte;
	int				tts;
	int				number_eat;
	int				phil_n;
	sem_t			*forks;
	struct timeval	start;
	int				ded;
	const char		*sem;
}	t_info_b;

void			error_msg(int err);
int				long_atoi(const char *nptr);
unsigned int	ts(struct timeval tv1, struct timeval tv2);
void			msleep(int value);
void			get_values_b(int argc, char **argv, t_info_b *phil_info);
void			fork_msg_b(t_info_b info, int id, int act);
int				is_ded_b(int id, unsigned int eaten, t_info_b phil_info);
void			thinking_b(t_info_b info, int id);
void			sleeping_b(t_info_b info, int id);
void			one_philo_b(t_info_b id);

#endif
