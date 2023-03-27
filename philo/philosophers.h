/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehasalu <ehasalu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 13:57:07 by ehasalu           #+#    #+#             */
/*   Updated: 2023/03/26 18:31:36 by ehasalu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <sys/time.h>
# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <semaphore.h>

typedef struct s_info
{
	int				ttd;
	int				tte;
	int				tts;
	int				number_eat;
	int				phil_n;
	int				*forks;
	struct timeval	start;
	int				ded;
}	t_info;

typedef struct s_id
{
	t_info			*info;
	int				id;
	int				t_eat;
	pthread_mutex_t	*mutexes;
}	t_id;

void			error_msg(int err);
int				long_atoi(const char *nptr);
void			one_philo(t_info id);
void			free_stuff(pthread_t **phil, pthread_mutex_t **mutexes,
					t_id **phil_id, t_info *phil_info);
unsigned int	ts(struct timeval tv1, struct timeval tv2);
void			msleep(int value);
int				is_ded(t_id *id, unsigned int eaten);
void			fork_msg(t_id *id, int pos, int act);
void			pick_fork(t_id *id, int pos);
void			put_fork(t_id *id, int pos);
void			get_values(int argc, char **argv, t_info *phil_info);
void			phil_init(t_info *phil_info,
					pthread_mutex_t **mutexes, t_id **phil_id);
void			memory_init(t_info *phil_info, pthread_t **phil,
					pthread_mutex_t **mutexes, t_id **phil_id);
void			sleeping(t_id *id);
void			thinking(t_id *id);
int				eat_last(t_id *id, int *t_eat, struct timeval l_eat);
int				eat(t_id *id, int *t_eat, struct timeval l_eat);
void			first_sleep(t_id *id, int *flag, struct timeval *last_eat);
void			*routine(void *phil_id);

#endif
