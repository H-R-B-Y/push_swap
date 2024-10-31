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
	if (st->i_max > st->top)
		st->i_max = 0;
	else if (st->i_max < 0)
		st->i_max = st->top;
	if (st->i_min > st->top)
		st->i_min = 0;
	else if (st->i_min < 0)
		st->i_min = st->top;
}

void	push_a(t_data *dat)
// pa (push a): Take the first element at the top of b and put it at the top of a.
// Do nothing if b is empty.
{
	int	val;

	if (!dat || is_empty(dat->b))
		return ;
	val = pop(dat->b);
	push(dat->a, val);
	if (dat->a->i_max == -1 || dat->a->items[dat->a->i_max] < val)
		dat->a->i_max = dat->a->top;
	if (dat->a->i_min == -1 || dat->a->items[dat->a->i_min] > val)
		dat->a->i_min = dat->a->top;
	ft_lstadd_back(&dat->ops_head, ft_lstnew(ft_strdup("pa")));
}

void	push_b(t_data *dat)
// pb (push b): Take the first element at the top of a and put it at the top of b.
// Do nothing if a is empty.
{
	int val;

	if (!dat || is_empty(dat->a))
		return ;
	val = pop(dat->a);
	push(dat->b, val);
	if (dat->b->i_max == -1 || dat->b->items[dat->b->i_max] < val)
		dat->b->i_max = dat->b->top;
	if (dat->b->i_min == -1 || dat->b->items[dat->b->i_min] > val)
		dat->b->i_min = dat->b->top;
	ft_lstadd_back(&dat->ops_head, ft_lstnew(ft_strdup("pb")));
}
