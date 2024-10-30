/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-29 16:12:10 by hbreeze           #+#    #+#             */
/*   Updated: 2024-10-29 16:12:10 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"


void	_min_max(t_stack *st)
{
	long long i;
	t_pos min;
	t_pos max;

	i = 0;
	min.val = st->items[st->top];
	min.pos = st->top;
	max.pos = st->top;
	max.val = st->items[st->top];
	if (!st || is_empty(st))
		return ;
	while (i <= st->top)
	{
		if (st->items[i] > max.val)
			max = (t_pos){st->items[i], i};
		else if (st->items[i] < min.val)
			min = (t_pos){st->items[i], i};
		i++;
	}
	st->i_max = max.pos;
	st->i_min = min.pos;
}

void	push_a(t_data *dat)
// pa (push a): Take the first element at the top of b and put it at the top of a.
// Do nothing if b is empty.
{
	if (!dat || is_empty(dat->b))
		return ;
	push(dat->a, pop(dat->b));
	ft_lstadd_back(&dat->ops_head, ft_lstnew(ft_strdup("pa")));
}

void	push_b(t_data *dat)
// pb (push b): Take the first element at the top of a and put it at the top of b.
// Do nothing if a is empty.
{
	if (!dat || is_empty(dat->a))
		return ;
	push(dat->b, pop(dat->a));
	ft_lstadd_back(&dat->ops_head, ft_lstnew(ft_strdup("pb")));
}
