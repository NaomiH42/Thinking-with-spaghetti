/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehasalu <ehasalu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 20:01:32 by ehasalu           #+#    #+#             */
/*   Updated: 2023/02/28 20:41:06 by ehasalu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h>

int	assign_len(int i, t_size aaa, int flag)
{
	if (!flag)
	{
		if (i == 10)
			return (aaa.len_last);
		else
			return (aaa.len);
	}
	else
	{
		if (i == 4)
			return (aaa.len_last);
		else
			return (aaa.len);
	}
}

void	over_hun(t_stack **a, t_stack **b, int **sep, t_size aaa)
{
	int			hold_first;
	int			hold_second;
	int			mov_num;
	static int	i;
	int			bbb;

	bbb = assign_len(i, aaa, 0);
	hold_first = scan_stack(a, sep[i], 1, bbb);
	hold_second = scan_stack(a, sep[i], 0, bbb);
	if ((find_pos(a, hold_first) - 1)
		< (lst_len(*a) - find_pos(a, hold_second)))
		mov_num = hold_first;
	else
		mov_num = hold_second;
	move_to_top(a, mov_num, 'a');
	if (lst_len(*b))
		move_b(b, mov_num);
	pb(a, b);
	if (scan_stack(a, sep[i], 1, bbb) == DW_ABOUT_IT && i < 11)
		i++;
	if (i == 11)
		return ;
	over_hun(a, b, sep, aaa);
}

void	under_hun(t_stack **a, t_stack **b, int **sep, t_size aaa)
{
	int			hold_first;
	int			hold_second;
	int			mov_num;
	static int	i;
	int			bbb;

	bbb = assign_len(i, aaa, 1);
	hold_first = scan_stack(a, sep[i], 1, bbb);
	hold_second = scan_stack(a, sep[i], 0, bbb);
	if ((find_pos(a, hold_first) - 1)
		< (lst_len(*a) - find_pos(a, hold_second)))
		mov_num = hold_first;
	else
		mov_num = hold_second;
	move_to_top(a, mov_num, 'a');
	if (lst_len(*b))
		move_b(b, mov_num);
	pb(a, b);
	if (scan_stack(a, sep[i], 1, bbb) == DW_ABOUT_IT && i < 5)
		i++;
	if (i == 5)
		return ;
	under_hun(a, b, sep, aaa);
}

char	**split_numbers(int *argc, char **argv, int *flag)
{
	char	**splitted;
	int		i;
	char	*temp;

	i = 0;
	if (numlen(ft_atoi(argv[1])) == (int)ft_strlen(argv[1]))
		return (argv);
	temp = ft_strjoin("0 ", argv[1]);
	splitted = ft_split(temp, ' ');
	while (splitted[i])
		i++;
	*argc = i;
	*flag = 1;
	free(temp);
	return (splitted);
}

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
