/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-29 16:23:54 by hbreeze           #+#    #+#             */
/*   Updated: 2024-10-29 16:23:54 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

static void	_rot(t_stack *st)
{
	int			tmp;
	long long	index;

	tmp = st->items[st->top];
	index = st->top;
	while (index > 0)
	{
		st->items[index]
			= st->items[index - 1];
		index--;
	}
	st->items[0] = tmp;
	st->i_max++;
	st->i_min++;
	_min_max(st);
}

void	rot_a(t_data *dat)
// ra (rotate a): Shift up all elements of stack a by 1.
// The first element becomes the last one.
{
	if (!dat || is_empty(dat->a)
		|| dat->a->top <= 0)
		return ;
	_rot(dat->a);
	ft_lstadd_back(&dat->ops_head, ft_lstnew(ft_strdup("ra")));
}

void	rot_b(t_data *dat)
// rb (rotate b): Shift up all elements of stack b by 1.
// The first element becomes the last one.
{
	if (!dat || is_empty(dat->b)
		|| dat->b->top == 0)
		return ;
	_rot(dat->b);
	ft_lstadd_back(&dat->ops_head, ft_lstnew(ft_strdup("rb")));
}

void	rot_rot(t_data *dat)
// rr : ra and rb at the same time.
{
	int	logged;

	if (!dat)
		return ;
	logged = 0;
	if (!is_empty(dat->a) && dat->a->top > 0 && ++logged)
		_rot(dat->a);
	if (!is_empty(dat->b) && dat->b->top > 0 && ++logged)
		_rot(dat->b);
	if (logged)
		ft_lstadd_back(&dat->ops_head, ft_lstnew(ft_strdup("rr")));
}
