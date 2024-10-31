/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-31 15:53:47 by hbreeze           #+#    #+#             */
/*   Updated: 2024-10-31 15:53:47 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

// Moves item at index to top of stack in least number of operations.
void	move_to_top(t_data *dat, t_stack *st, long long index)
{
	long long	mid;
	void		(*f)(t_data *);
	long long	iter;

	if (index == st->top)
		return ;
	mid = st->top / 2;
	f = st->ops[(REV * (index < mid)) + (ROT * !(index < mid))];
	if (index < mid)
		iter = index;
	else
		iter = (st->top - index);
	while (iter--)
		f(dat);
}

void	perform_operation_lst(t_data *dat, t_list *lst)
{
	t_list		*index;
	t_op_desc	*operations;

	index = lst;
	while (index)
	{
		operations = (t_op_desc *)index->content;
		while (operations->count--)
			operations->st->ops[operations->op](dat);
		index = index->next;
	}
	
}

void do_sort(t_data *dat)
{
	t_opc *cur_op;

	dat->a->ops[PUSH](dat);
	dat->a->ops[PUSH](dat);

	// calculate move of least cost!
	while (!is_empty(dat->a))
	{
		// Returns a list of operations to perform and the length of the list.
		cur_op = get_least_cost(dat->a, dat->b);
		perform_operation_lst(dat, cur_op->ops);
		print_stacks(dat);
		destroy_cost(cur_op);
	}
	move_to_top(dat, dat->b, dat->b->i_max);
	while(!is_empty(dat->b))
	{
		dat->b->ops[PUSH](dat);
		print_stacks(dat);
	}
	print_state(dat);
}
