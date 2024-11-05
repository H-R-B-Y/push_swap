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

// int is_sorted_recursive(int *items, size_t index, size_t size, int direction) {
// 	if (index >= size - 1) {
// 		return direction; // Base case: reached the end, return the sorting direction
// 	}
// 	if (direction == 0) {
// 		// Determine sorting direction based on the first comparison
// 		if (items[index] < items[index + 1]) {
// 			direction = 1;  // Ascending
// 		} else if (items[index] > items[index + 1]) {
// 			direction = -1; // Descending
// 		} else {
// 			return 0;  // Equal elements found, treat as unsorted
// 		}
// 	}
// 	// Check if current pair matches the determined sorting direction
// 	if ((direction == 1 && items[index] > items[index + 1]) ||
// 		(direction == -1 && items[index] < items[index + 1])) {
// 		return 0;  // Not sorted
// 	}
// 	// Recur with the next element
// 	return is_sorted_recursive(items, index + 1, size, direction);
// }
// int check_stack_sorted(t_stack *st) {
// 	if (st == 0 || st->items == 0 || st->top == 0) {
// 		return 0;  // Invalid input or empty stack, consider as unsorted
// 	}
// 	return is_sorted_recursive(st->items, 0, st->top + 1, 0);
// }

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
	ft_printf("%d\n", ft_lstsize(dat->ops_head));
	print_stack(dat->a);
}
