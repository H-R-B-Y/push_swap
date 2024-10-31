/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cost.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-31 12:22:37 by hbreeze           #+#    #+#             */
/*   Updated: 2024-10-31 12:22:37 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// calculate the cost to move a index to top of stack in least ops.
size_t	cost_to_move_to_top(t_opc *cst, t_stack *st , long long index)
{
	long long mid;

	if (index == st->top)
		return (0);
	mid = st->top / 2;
	if (index < mid)
	{
		append_ops(cst, st, REV, index + 1);
		return (index + 1);
	}
	else
	{
		append_ops(cst, st, ROT, st->top - index);
		return (st->top - index);
	}
}

// calculate the cost for a poisition that is not min or max.
// I have no idea what I am doing here T-T
/*
6

V		I		M
1		3		
				1
7		2		
// goes here which is 2 rotations
5		1		
				3
2		0		
*/
size_t	cost_for_position(t_opc *cst, t_stack *st, int value)
{

	long long index;

	index = st->top;
	while (index > 0)
	{
		if (value < st->items[index] && value > st->items[index - 1])
			return (cost_to_move_to_top(cst, st, index - 1));
		index--;
	}
	return (0);
}


// get the cost of moving item at index in from to correct position in too
t_opc	*get_cost(t_stack *from, t_stack *too, long long index)
{
	t_opc	*cost;

	cost = create_cost(index);
	// cost->op_count = 1; // We always need to push so it will always be atleast 1;
	// cost to move it to the top of the stack!
	cost->op_count += cost_to_move_to_top(cost, from, index);

	if (from->items[index] > too->items[too->i_max])
	{
		cost->op_count += cost_to_move_to_top(cost, too, too->i_max);
	}
	else if (from->items[index] < too->items[too->i_min])
	{
		cost->op_count += cost_to_move_to_top(cost, too, too->i_max);
	}
	else
	{ // If it is not the newest min or max value we need to find where to put it
		if (too->i_min - too->i_max == 0)
		{
			append_ops(cost, too, ROT, 1);
			cost->op_count += 1;
		}
		else
		{
			cost->op_count += cost_for_position(cost, too, from->items[index]);
		}
	}
	cost->op_count += 1;
	append_ops(cost, from, PUSH, 1);
	return (cost);
}

// Find the number with the least cost.
t_opc	*get_least_cost(t_stack *from, t_stack *too)
{
	long long index;
	t_opc	*current_least;
	t_opc	*temp;

	index = from->top;
	current_least = get_cost(from, too, index--);
	while (current_least->op_count != 2 && index >= 0) // loop through all items in from
	{
		temp = get_cost(from, too, index--);
		if (temp->op_count < current_least->op_count)
		{
			destroy_cost(current_least);
			current_least = temp;
		}
		else
			destroy_cost(temp);
	}
	return (current_least);
}
