/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-29 17:09:56 by hbreeze           #+#    #+#             */
/*   Updated: 2024-10-29 17:09:56 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "limits.h"

// calculate the cost to move a index to top of stack in least ops.
size_t	cost_to_move_to_top(t_stack *st, long long index)
{
	long long	mid;

	if (index == st->top)
		return (0);
	mid = st->top / 2;
	if (index < mid)
		return (index + 1); // reverse rotate
	else
		return (st->top - index); // rotate to the front?
}

// calculate the cost for a poisition that is not min or max.
size_t	cost_for_position(t_stack *st, int value)
{
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
	long long index;

	index = st->top;
	while (index > 0)
	{
		if (value < st->items[index] && value > st->items[index - 1])
			return (st->top - index + 1);
		index--;
	}
	return (0);
}

// get the cost of moving item at index in from to correct position in too
t_opc	get_cost(t_stack *from, t_stack *too, long long index)
{
	t_opc	cost;

	cost.index = index;
	cost.op_count = 1; // We always need to push so it will always be atleast 1;
	// cost to move it to the top of the stack!
	cost.op_count += cost_to_move_to_top(from, index);
	if (from->items[index] > too->items[too->i_max])
		cost.op_count += cost_to_move_to_top(too, too->i_max);
	else if (from->items[index] < too->items[too->i_min])
		cost.op_count += cost_to_move_to_top(too, too->i_max) + 1;
	else
	{ // If it is not the newest min or max value we need to find where to put it
		if (too->i_min - too->i_max == 1 || too->i_min - too->i_max == -1)
			cost.op_count += 1;
		else
			cost.op_count += cost_for_position(too, from->items[index]);
	}
	return (cost);
}

// Find the number with the least cost.
t_opc	get_least_cost(t_stack *from, t_stack *too)
{
	long long index;
	t_opc	current_least;
	t_opc	temp;

	_min_max(too);
	_min_max(from);
	index = from->top;
	current_least = get_cost(from, too, index--);
	while (current_least.op_count != 2 && index >= 0) // loop through all items in from
	{
		temp = get_cost(from, too, index--);
		if (temp.op_count < current_least.op_count)
			current_least = temp;
	}
	return (current_least);
}

// Moves item at index to top of stack in least number of operations.
void	move_to_top(t_data *dat, t_stack *st, long long index)
{
	long long	mid;

	if (index == st->top)
		return ;
	mid = st->top / 2;
	if (index < mid)
	{
		index++;
		while ((index)--)
		{
			if (st == dat->a)
				rev_a(dat);
			else
				rev_b(dat);
			print_stacks(dat);
		}
	}
	else
	{
		while (index++ < st->top)
		{
			if (st == dat->a)
				rot_a(dat);
			else
				rot_b(dat);
			print_stacks(dat);
		}
	}
}

// Find the correct position of value in st 
// and then rotate so that value can be pushed to the top (correct position)
void	index_above(t_data *dat, t_stack *st, int value)
{
	long long	index;

	index = st->top;
	if (value > st->items[st->i_max] || value < st->items[st->i_min])
	{
		move_to_top(dat, st, st->i_max);
		return ;
	}
	while (index > 0)
	{
		if (value < st->items[index] && value > st->items[index - 1])
		{
			move_to_top(dat, st, index - 1);
			return ;
		}
		index--;
	}
}

// Move an index in st to the correct place in the opposite stack
void	move_to_position(t_data *dat, t_stack *st, long long index)
{
	int value;

	if (st == dat->a)
	{
		value = dat->a->items[index];
		_min_max(dat->b);
		move_to_top(dat, dat->a, index);
		_min_max(dat->b);
		index_above(dat, dat->b, value);
		push_b(dat);
		print_stacks(dat);
	}
	else
	{
		value = dat->b->items[index];
		_min_max(dat->a);
		move_to_top(dat, dat->b, index);
		_min_max(dat->a);
		index_above(dat, dat->a, value);
		push_a(dat);
		print_stacks(dat);
	}

}

void do_sort(t_data *dat)
{
	t_opc cur_op;

	push_b(dat);
	push_b(dat);
	print_stacks(dat);

	// calculate move of least cost!
	while (!is_empty(dat->a))
	{
		// calculates the cost of operations to move it into the right position.
		cur_op = get_least_cost(dat->a, dat->b);
		// This will do the movement, but  it will need to re-calculate the 
		// movement/rotations that were calculated in above step 
		// should probably be returned from the calculation in some form
		move_to_position(dat, dat->a, cur_op.index);
	}
	_min_max(dat->b);
	move_to_top(dat, dat->b, dat->b->i_max);
	while(!is_empty(dat->b))
	{
		push_a(dat);
		print_stacks(dat);
	}

}

int main(void)
{
	t_data *dat;
	
	dat = init_data(21);
	ft_printf("%d\n", dat->max_size);
	push(dat->a, 9);
	push(dat->a, 0);
	push(dat->a, 8);
	push(dat->a, 7);
	push(dat->a, 1);
	push(dat->a, 6);
	push(dat->a, 4);
	push(dat->a, 5);
	push(dat->a, 3);
	push(dat->a, 10);
	push(dat->a, 2);
	

	push(dat->a, 9 + 10);
	push(dat->a, 8 + 10);
	push(dat->a, 7 + 10);
	push(dat->a, 1 + 10);
	push(dat->a, 6 + 10);
	push(dat->a, 4 + 10);
	push(dat->a, 5 + 10);
	push(dat->a, 3 + 10);
	push(dat->a, 10 + 10);
	push(dat->a, 2 + 10);
	print_state(dat);
	do_sort(dat);
	print_state(dat);
	// Optimise the ops stack.
	destory_data(dat);
}


// int main(void)
// {
// 	t_data *dat;
	
// 	dat = init_data(11);
// 	ft_printf("%d\n", dat->max_size);
// 	push(dat->a, 6);
// 	push(dat->a, 5);
// 	push(dat->a, 4);
// 	push(dat->a, 3);
// 	push(dat->a, 1);
// 	push(dat->a, 2);
// 	print_stacks(dat);
// 	swap_a(dat);
// 	print_stacks(dat);
// 	push_b(dat);
// 	push_b(dat);
// 	push_b(dat);
// 	print_stacks(dat);
// }