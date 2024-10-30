/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rev_rotations.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-29 16:38:38 by hbreeze           #+#    #+#             */
/*   Updated: 2024-10-29 16:38:38 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

static void	_rev_rot(t_stack *st)
{
	int			tmp;
	long long	index;

	tmp = st->items[0];
	index = 0;
	while (index < st->top)
	{
		st->items[index]
			= st->items[index + 1];
		index++;
	}
	st->items[st->top] = tmp;
}

void	rev_a(t_data *dat)
// rra (reverse rotate a): Shift down all elements of stack a by 1.
// The last element becomes the first one.
{
	if (!dat || is_empty(dat->a)
		|| dat->a->top <= 0)
		return ;
	_rev_rot(dat->a);
	ft_lstadd_back(&dat->ops_head, ft_lstnew(ft_strdup("rra")));
}

void	rev_b(t_data *dat)
// rrb (reverse rotate b): Shift down all elements of stack b by 1.
// The last element becomes the first one.
{
	if (!dat || is_empty(dat->b)
		|| dat->b->top <= 0)
		return ;
	_rev_rot(dat->b);
	ft_lstadd_back(&dat->ops_head, ft_lstnew(ft_strdup("rrb")));
}

void	rev_rev(t_data *dat)
// rrr : rra and rrb at the same time
{
	int logged;

	if (!dat)
		return ;
	logged = 0;
	if (!is_empty(dat->a) && dat->a->top > 0 && ++logged)
		_rev_rot(dat->a);
	if (!is_empty(dat->b) && dat->b->top > 0 && ++logged)
		_rev_rot(dat->b);
	if (logged)
		ft_lstadd_back(&dat->ops_head, ft_lstnew(ft_strdup("rrr")));
}
