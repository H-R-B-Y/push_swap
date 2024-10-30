/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_stack.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-29 15:42:11 by hbreeze           #+#    #+#             */
/*   Updated: 2024-10-29 15:42:11 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_stack	*init_stack(size_t max_size)
{
	t_stack *st;

	st = zeroit(malloc(sizeof(t_stack)), sizeof(t_stack));
	if (!st)
		return (0);
	st->items = malloc(sizeof(int) * max_size);
	st->top = -1;
	st->i_max = -1;
	st->i_max = -1;
	return (st);
}

void	destroy_stack(t_stack *st)
{
	if (!st)
		return ;
	free(st->items);
	free(st);
}
