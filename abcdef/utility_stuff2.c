/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_stuff2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehasalu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 13:05:36 by ehasalu           #+#    #+#             */
/*   Updated: 2023/03/01 13:05:37 by ehasalu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	algorithm_stuff(t_stack **a, int i)
{
	if (case1(a))
		sa(a);
	if (case2(a))
	{
		sa(a);
		if (i == 1)
			rra(a);
	}
	if (case3(a))
	{
		if (i == 1)
			ra(a);
	}
	if (case4(a))
	{
		sa(a);
		if (i == 1)
			ra(a);
	}
	if (case5(a))
	{
		if (i == 1)
			rra(a);
	}
}

int	highest(t_stack **lst)
{
	int	num;
	int	i;

	i = 1;
	num = INT_MIN;
	while (i <= lst_len(*lst))
	{
		if (vop(lst, i) > num)
			num = vop(lst, i);
		i++;
	}
	return (num);
}

int	closest(t_stack **lst, int num)
{
	int	i;

	i = 1;
	while (i <= lst_len(*lst))
	{
		if (vop(lst, i) < num && vop(lst, i + 1) > num)
			return (vop(lst, i + 1));
		i++;
	}
	return (highest(lst));
}

int	lowest(t_stack **lst)
{
	int	num;
	int	i;

	i = 1;
	num = vop(lst, i);
	while (i <= lst_len(*lst))
	{
		if (vop(lst, i) < num)
			num = vop(lst, i);
		i++;
	}
	return (num);
}

int	sn_lowest(t_stack **lst, int num)
{
	int	res;
	int	i;

	i = 1;
	res = INT_MIN;
	while (i <= lst_len(*lst))
	{
		if (vop(lst, i) > res && vop(lst, i) < num)
			res = vop(lst, i);
		i++;
	}
	return (res);
}
