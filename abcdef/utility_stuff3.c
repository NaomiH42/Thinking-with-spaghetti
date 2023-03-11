/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_stuff3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehasalu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 13:05:38 by ehasalu           #+#    #+#             */
/*   Updated: 2023/03/01 13:05:39 by ehasalu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	put_a_to_b(t_stack **a, t_stack **b)
{
	while (!b_is_empty(a))
	{
		while (vop(a, 1) != highest(a))
			ra(a);
		pb(a, b);
	}
}

void	put_b_to_a(t_stack **a, t_stack **b)
{
	if (!b_is_empty(b))
	{
		while (vop(b, 1) != highest(b))
			rb(b);
		pa(a, b);
	}
}

int	scan_stack1(t_stack **lst, int *array, int aaa)
{
	int	i;
	int	l;

	l = 1;
	while (l <= lst_len(*lst))
	{
		i = 0;
		while (i < aaa)
		{
			if (vop(lst, l) == array[i])
				return (array[i]);
			i++;
		}
		l++;
	}
	return (DW_ABOUT_IT);
}

int	scan_stack2(t_stack **lst, int *array, int aaa)
{
	int	i;
	int	l;

	l = lst_len(*lst);
	while (l > 0)
	{
		i = 0;
		while (i < aaa)
		{
			if (vop(lst, l) == array[i])
				return (array[i]);
			i++;
		}
		l--;
	}
	return (DW_ABOUT_IT);
}

int	scan_stack(t_stack **lst, int *array, int direction, int aaa)
{
	if (direction == 1)
	{
		return (scan_stack1(lst, array, aaa));
	}
	else
	{
		return (scan_stack2(lst, array, aaa));
	}
	return (DW_ABOUT_IT);
}
