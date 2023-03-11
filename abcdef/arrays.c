/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrays.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehasalu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 13:29:37 by ehasalu           #+#    #+#             */
/*   Updated: 2023/03/01 13:29:38 by ehasalu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	**create_arrays_big2(t_stack **a, t_size *aaa, int *arr)
{
	int	**arrays;
	int	k;
	int	i;
	int	l;

	i = 0;
	k = 0;
	arrays = ft_calloc(sizeof(int *), 11);
	aaa->len = lst_len(*a) / 11;
	aaa->len_last = (lst_len(*a) - ((lst_len(*a) / 11) * 10));
	while (i < 10)
	{
		l = 0;
		arrays[i] = malloc(sizeof(int) * ((lst_len(*a) / 11)));
		while (l < lst_len(*a) / 11)
			arrays[i][l++] = arr[k++];
		i++;
	}
	arrays[i] = malloc(sizeof(int) * (((lst_len(*a)
						- (lst_len(*a) / 11) * 10))));
	l = 0;
	while (l < (lst_len(*a) - (lst_len(*a) / 11) * 10))
		arrays[i][l++] = arr[k++];
	return (arrays);
}

int	**create_arrays_big(t_stack **a, t_size *aaa)
{
	int	i;
	int	num;
	int	*arr;
	int	**arrays;

	i = 1;
	num = highest(a);
	arr = malloc(sizeof(int) * lst_len(*a));
	arr[lst_len(*a) - i] = num;
	while (i < lst_len(*a))
	{
		i++;
		arr[lst_len(*a) - i] = sn_lowest((a), num);
		num = sn_lowest((a), num);
	}
	arrays = create_arrays_big2(a, aaa, arr);
	free(arr);
	return (arrays);
}

int	**create_arrays2(t_stack **a, t_size *aaa, int *arr)
{
	int	**arrays;
	int	k;
	int	i;
	int	l;

	i = 0;
	k = 0;
	arrays = ft_calloc(sizeof(int *), 6);
	aaa->len = lst_len(*a) / 5;
	aaa->len_last = (lst_len(*a) - ((lst_len(*a) / 5) * 4));
	while (i < 4)
	{
		l = 0;
		arrays[i] = malloc(sizeof(int) * ((lst_len(*a) / 5)));
		while (l < lst_len(*a) / 5)
			arrays[i][l++] = arr[k++];
		i++;
	}
	arrays[i] = malloc(sizeof(int) * (((lst_len(*a) - (lst_len(*a) / 5) * 4))));
	l = 0;
	while (l < (lst_len(*a) - (lst_len(*a) / 5) * 4))
		arrays[i][l++] = arr[k++];
	return (arrays);
}

int	**create_arrays(t_stack **a, t_size *aaa)
{
	int	i;
	int	num;
	int	*arr;
	int	**arrays;

	i = 1;
	num = highest(a);
	arr = ft_calloc(sizeof(int), lst_len(*a));
	arr[lst_len(*a) - i] = num;
	while (i < lst_len(*a))
	{
		i++;
		arr[lst_len(*a) - i] = sn_lowest((a), num);
		num = sn_lowest((a), num);
	}
	arrays = create_arrays2(a, aaa, arr);
	free(arr);
	return (arrays);
}
