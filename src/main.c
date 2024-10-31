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
		print_stacks(dat);
	}
	
}

void do_sort(t_data *dat)
{
	t_opc *cur_op;

	dat->a->ops[PUSH](dat);
	dat->a->ops[PUSH](dat);
	print_stacks(dat);

	// calculate move of least cost!
	while (!is_empty(dat->a))
	{
		// Returns a list of operations to perform and the length of the list.
		cur_op = get_least_cost(dat->a, dat->b);
		perform_operation_lst(dat, cur_op->ops);
		destroy_cost(cur_op);
	}
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
	//ft_printf("%d\n", dat->max_size);
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