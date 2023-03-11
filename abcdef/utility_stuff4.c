/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_stuff4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehasalu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 13:05:42 by ehasalu           #+#    #+#             */
/*   Updated: 2023/03/01 13:05:43 by ehasalu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	closest2(t_stack **lst, int num)
{
	int	i;
	int	res;

	i = 1;
	res = highest(lst);
	while (i < lst_len(*lst))
	{
		if (vop(lst, i) > num && vop(lst, i) < res)
			res = vop(lst, i);
		i++;
	}
	return (res);
}

int	low_big_or(t_stack **lst, int num)
{
	if (num > highest(lst))
		return (1);
	else if (num < lowest(lst))
		return (-1);
	else
		return (0);
}

void	move_b(t_stack **b, int num)
{
	if (low_big_or(b, num) == 1)
		move_to_top(b, lowest(b), 'b');
	else if ((low_big_or(b, num) == -1))
		move_to_top(b, lowest(b), 'b');
	else
		move_to_top(b, closest2(b, num), 'b');
}
