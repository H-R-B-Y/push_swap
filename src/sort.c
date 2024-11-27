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

#include "push_swap.h"

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
		iter = index + 1;
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
void sort_three(t_stack *st)
{
	int *i;

	i = st->items;
	if (i[st->top] < i[st->top - 1] && i[st->top -1] < i[st->top - 2])
		return ;
	if (i[st->top] < i[st->top - 1] && i[st->top - 1] > i[st->top - 2])
	{
		st->ops[REV](st->meta);
		sort_three(st);
		return ;
	}
	else if ((i[st->top] > i[st->top - 1] && i[st->top - 1] > i[st->top - 2])
		|| (i[st->top] > i[st->top - 1] && i[st->top - 1] < i[st->top - 2]))
	{
		st->ops[SWAP](st->meta);
		sort_three(st);
		return ;
	}
}

void push_back(t_stack *from, t_stack *too, int count)
{
	while (!is_empty(from))
	{
		while (too->items[0] > from->items[from->top] && count && count--)
			too->ops[REV](too->meta);
		from->ops[PUSH](from->meta);
	}
	while (too->items[0] < too->items[too->top] && count && count--)
		too->ops[REV](too->meta);
}

void do_sort(t_data *dat)
{
	t_opc	*cur_op;

	while (dat->a->top > 2)
	{
		cur_op = get_least_cost(dat->a, dat->b);
		perform_operation_lst(dat, cur_op->ops);
		destroy_cost(cur_op);
	}
	sort_three(dat->a);
	move_to_top(dat, dat->b, dat->b->i_max);
	push_back(dat->b, dat->a, dat->a->top + 1);
	print_ops(dat);
}
