/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   under_five.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehasalu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 13:06:00 by ehasalu           #+#    #+#             */
/*   Updated: 2023/03/01 13:06:01 by ehasalu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	closest3(t_stack **lst, int num)
{
	int	i;
	int	res;

	i = 1;
	res = highest(lst);
	while (i <= lst_len(*lst))
	{
		if (vop(lst, i) > num && vop(lst, i) < res)
			res = vop(lst, i);
		i++;
	}
	return (res);
}

void	under_five(t_stack **a, t_stack **b)
{
	if (lst_len(*a) < 3)
	{
		if (vop(a, 1) > vop(a, 2))
			sa(a);
	}
	else if (lst_len(*a) == 3)
		algorithm_stuff(a, 1);
	else
	{
		while (lst_len(*a) != 3 && !a_is_sort(a))
			pb(a, b);
		algorithm_stuff(a, 1);
		while (!b_is_empty(b))
		{
			if (vop(b, 1) > highest(a))
				move_to_top(a, lowest(a), 'a');
			else if (vop(b, 1) < lowest(a))
				move_to_top(a, lowest(a), 'a');
			else
				move_to_top(a, closest3(a, vop(b, 1)), 'a');
			pa(a, b);
		}
		while (vop(a, 1) != lowest(a))
			ra(a);
	}
}
