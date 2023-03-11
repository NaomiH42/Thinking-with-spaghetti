/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_stuff.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehasalu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 13:05:33 by ehasalu           #+#    #+#             */
/*   Updated: 2023/03/01 13:05:34 by ehasalu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_stack	*get_last(t_stack *lst)
{
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}

int	vop(t_stack **lst, int pos)
{
	int		i;
	t_stack	*temp;

	i = 1;
	temp = *lst;
	while (i != pos && temp->next != NULL && temp != NULL)
	{
		temp = temp->next;
		i++;
	}
	return (temp->content);
}

int	lst_len(t_stack *lst)
{
	t_stack	*temp;
	int		i;

	i = 1;
	if (lst == NULL)
		return (0);
	temp = lst;
	while (temp->next != NULL)
	{
		temp = temp->next;
		i++;
	}
	return (i);
}

int	b_is_empty(t_stack **b)
{
	if (*b != NULL)
		return (0);
	return (1);
}

int	a_is_sort(t_stack **a)
{
	int	i;

	i = 1;
	while (i <= lst_len(*a))
	{
		if (vop(a, i) > vop(a, i + 1))
			return (0);
		i++;
	}
	return (1);
}
