/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-29 15:44:44 by hbreeze           #+#    #+#             */
/*   Updated: 2024-10-29 15:44:44 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "push_swap.h"

int	push(t_stack *st, int value)
{
	if (!st)
		return (0);
	if (st->top + 1 > (long long)*st->max_size)
		return (0);
	st->top++;
	st->items[st->top] = value;
	return (1);
}

int	pop(t_stack *st)
{
	if (!st)
		return (0);
	if (st->top < 0)
		return (0);
	st->top--;
	return (st->items[st->top + 1]);
}

int	is_empty(const t_stack *st)
{
	if (!st)
		return (0);
	return (st->top == -1);
}
