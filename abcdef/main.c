/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehasalu <ehasalu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 20:01:32 by ehasalu           #+#    #+#             */
/*   Updated: 2023/03/11 18:35:40 by ehasalu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	static int		i;
	static int		flag;
	t_stack			*stacks[3];

	if (argc == 1)
		return (0);
	if (argc == 2)
		argv = split_numbers(&argc, argv, &flag);
	check_arg(argc, argv);
	if (argc == 2)
		return (0);
	stacks[0] = malloc(sizeof(*stacks[0]));
	stacks[0]->content = ft_atoi(argv[++i]);
	stacks[2] = stacks[0];
	stacks[1] = NULL;
	while (++i < argc)
	{
		stacks[2]->next = ft_calloc(sizeof (*stacks[0]), 1);
		stacks[2] = stacks[2]->next;
		stacks[2]->content = ft_atoi(argv[i]);
	}
	if (!a_is_sort(&stacks[0]))
		operations(stacks[0], stacks[1], flag, argv);
	else
		free_stuff(NULL, &(stacks[0]), flag, argv);
}
