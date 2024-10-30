/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swaps.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-29 16:15:30 by hbreeze           #+#    #+#             */
/*   Updated: 2024-10-29 16:15:30 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

static void	_swap(t_stack *st)
{
	int	tmp;

	tmp = st->items[st->top];
	st->items[st->top] = st->items[st->top - 1];
	st->items[st->top - 1] = tmp;
}

void	swap_a(t_data *dat)
// sa (swap a): Swap the first 2 elements at the top of stack a.
// Do nothing if there is only one or no elements.
{
	if (!dat || dat->a->top <= 0)
		return ;
	_swap(dat->a);
	ft_lstadd_back(&dat->ops_head, ft_lstnew(ft_strdup("sa")));
}

void	swap_b(t_data *dat)
// sb (swap b): Swap the first 2 elements at the top of stack b.
// Do nothing if there is only one or no elements.
{
	if (!dat || dat->b->top <= 0)
		return ;
	_swap(dat->b);
	ft_lstadd_back(&dat->ops_head, ft_lstnew(ft_strdup("sb")));
}

void	swap_swap(t_data *dat)
// ss : sa and sb at the same time.
{
	if (!dat)
		return ;
	if (dat->a->top >= 1)
		_swap(dat->a);
	if (dat->b->top >= 1)
		_swap(dat->b);
	if (dat->b->top >= 1 || dat->a->top >= 1)
		ft_lstadd_back(&dat->ops_head, ft_lstnew(ft_strdup("ss")));
}
