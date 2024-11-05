/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cost_reduction.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-01 17:31:29 by hbreeze           #+#    #+#             */
/*   Updated: 2024-11-01 17:31:29 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*

if a_op is rev and (a->top - (rev-count - 1) < b-rot-count)
	then a-rev becomes rot-rot(-count = a->top - (rev-count - 1))
if a_op is rev and (a->top - (rev-count - 1) == b-rot-count)
	then delete a->op and b-rot becomes rot-rot

and vice versa.
*/

void	_less_diff_dir(
	t_opc *cost,
	t_op_desc *a_op,
	t_op_desc *b_op)
{
	int combined_count;

	if (a_op->op == REV && b_op->op == ROT)
	{
		combined_count = a_op->st->top - (a_op->count - 1);
		if (!(combined_count <= b_op->count))
			return ;
		a_op->op = RR; // Rotate both forward instead
	}
	else if (a_op->op == ROT && b_op->op == REV)
	{
		combined_count = (a_op->st->top - a_op->count) + 1;
		if (!(combined_count <= b_op->count)) // If reverse rotation is less costly
			return ;
		a_op->op = RRR; // Use reverse rotation instead
	}
	else
		return ;
	a_op->count = combined_count; // Set the count to achieve the desired index on top of a
	b_op->count -= combined_count; // Adjust b's count by removing the combined rotations
	cost->op_count = a_op->count + b_op->count;
}

void	reduce_diff_directions(
	t_opc *cost,
	t_op_desc *a_op,
	t_op_desc *b_op)
{
	if (a_op->count < b_op->count)
		_less_diff_dir(cost, a_op, b_op);
	else
		_less_diff_dir(cost, b_op, a_op);
}

void	reduce_same_direction(
	t_opc *cost,
	t_op_desc *a_op,
	t_op_desc *b_op)
{
	t_op_desc *less;
	t_op_desc *more;

	less = b_op;
	more = a_op;
	if (a_op->count < b_op->count)
	{
		less = a_op;
		more = b_op;
	}
	less->op = (RRR * (less->op == REV))
				+ (RR * (less->op == ROT));
	more->count -= less->count;
	cost->op_count -= less->count;
}

void	reduce_cost(t_opc *cost)
{
	t_op_desc	*a_op;
	t_op_desc	*b_op;

	if (ft_lstsize(cost->ops) < 2)
		return ;
	a_op = cost->ops->content;
	b_op = cost->ops->next->content;
	if (a_op->op == b_op->op)
	{
		if (a_op->count == b_op->count)
		{
			ft_lstdelone(cost->ops->next, free);
			cost->ops->next = 0;
			a_op->op = (RRR * (a_op->op == REV))
				+ (RR * (a_op->op == ROT));
			cost->op_count /= 2;
		}
		else
			reduce_same_direction(cost, a_op, b_op);
	}
	else
		reduce_diff_directions(cost, a_op, b_op);
	return ;
}
