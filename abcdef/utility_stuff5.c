/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_stuff5.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehasalu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 13:05:45 by ehasalu           #+#    #+#             */
/*   Updated: 2023/03/01 13:05:46 by ehasalu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h>

void	free_array(int ***arr, int flag)
{
	int	i;

	i = 0;
	if (flag)
	{
		while (i < 5)
		{
			free((*arr)[i]);
			i++;
		}
		free(*arr);
	}
	else
	{
		while (i < 11)
		{
			free((*arr)[i]);
			i++;
		}
		free(*arr);
	}
}

void	free_stuff(int ***arr, t_stack **a, int flag, char **argv)
{
	t_stack	*temp;
	int		i;

	i = 0;
	temp = *a;
	if (lst_len(*a) <= 100 && lst_len(*a) > 5 && arr)
		free_array(arr, 1);
	else if (lst_len(*a) > 100 && arr)
		free_array(arr, 0);
	while (*a != NULL)
	{
		temp = (*a)->next;
		free(*a);
		*a = temp;
	}
	if (flag)
	{
		while (argv[i])
			free(argv[i++]);
		free(argv);
	}
}

void	operations(t_stack *a, t_stack *b, int flag, char **argv)
{
	t_size	aaa;
	int		**sep;

	if (lst_len(a) <= 100 && lst_len(a) > 5)
		sep = create_arrays(&a, &aaa);
	else if (lst_len(a) > 100)
		sep = create_arrays_big(&a, &aaa);
	if (lst_len(a) == 1)
		exit(0);
	else if (lst_len(a) <= 5)
		under_five(&a, &b);
	else if (lst_len(a) <= 100)
	{
		under_hun(&a, &b, sep, aaa);
		while (!b_is_empty(&b))
			sort_push_b(&a, &b);
	}
	else
	{
		over_hun(&a, &b, sep, aaa);
		while (!b_is_empty(&b))
			sort_push_b(&a, &b);
	}
	free_stuff(&sep, &a, flag, argv);
}

void	move_to_top(t_stack **lst, int num, char stack_l)
{
	if (find_pos(lst, num) > (lst_len(*lst) / 2))
	{
		while (vop(lst, 1) != num)
		{
			if (stack_l == 'a')
				rra(lst);
			else
				rrb(lst);
		}
	}
	else
	{
		while (vop(lst, 1) != num)
		{
			if (stack_l == 'a')
				ra(lst);
			else
				rb(lst);
		}
	}
}

int	find_pos(t_stack **lst, int num)
{
	int	i;

	i = 1;
	while (i <= lst_len(*lst))
	{
		if (vop(lst, i) == num)
			return (i);
		i++;
	}
	return (0);
}
