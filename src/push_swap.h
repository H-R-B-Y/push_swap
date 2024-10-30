/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-29 15:11:46 by hbreeze           #+#    #+#             */
/*   Updated: 2024-10-29 15:11:46 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "../include/libft.h"
# include "../include/ft_printf.h"


// Typedefs:

typedef enum e_op_code {
	SA, SB, SS, PA, PB,
	RA, RB, RR,
	RRA, RRB, RRR,
	OP_CODE_COUNT
} t_op_code;

typedef struct s_pos
{
	int			val;
	long long	pos;
}	t_pos;

typedef struct s_opc
{
	long long	index;
	long long	op_count;
}	t_opc;

typedef struct s_stack {
	int				*items;
	long long		top;
	long long		*max_size;
	long long		i_max; // index of max item
	long long		i_min; // index of min item
	struct s_data	*meta;
}	t_stack;

typedef struct s_data
{
	t_stack 		*a;
	t_stack			*b;
	long long		max_size;
	t_list			*ops_head;
}	t_data;


// Generics:
t_data	*init_data(size_t max_size);
void	destory_data(t_data *dat);
t_stack	*init_stack(size_t max_size);
void	destroy_stack(t_stack *st);

int		push(t_stack *st, int value);
int		pop(t_stack *st);

int		is_empty(const t_stack *st);
int		is_full(const t_stack *st);

// Literals:

void	swap_a(t_data *dat); // sa
// sa (swap a): Swap the first 2 elements at the top of stack a.
// Do nothing if there is only one or no elements.

void	swap_b(t_data *dat); // sb
// sb (swap b): Swap the first 2 elements at the top of stack b.
// Do nothing if there is only one or no elements.

void	swap_swap(t_data *dat); //ss
// ss : sa and sb at the same time.

void	push_a(t_data *dat); // pa
// pa (push a): Take the first element at the top of b and put it at the top of a.
// Do nothing if b is empty.

void	push_b(t_data *dat); // pb
// pb (push b): Take the first element at the top of a and put it at the top of b.
// Do nothing if a is empty.

void	rot_a(t_data *dat); // ra
// ra (rotate a): Shift up all elements of stack a by 1.
// The first element becomes the last one.

void	rot_b(t_data *dat); // rb
// rb (rotate b): Shift up all elements of stack b by 1.
// The first element becomes the last one.

void	rot_rot(t_data *dat); // rr
// rr : ra and rb at the same time.

void	rev_a(t_data *dat); // rra
// rra (reverse rotate a): Shift down all elements of stack a by 1.
// The last element becomes the first one.

void	rev_b(t_data *dat); // rrb
// rrb (reverse rotate b): Shift down all elements of stack b by 1.
// The last element becomes the first one.

void	rev_rev(t_data *dat); //rrr
// rrr : rra and rrb at the same time

// Debug / Printing
void	print_state(t_data *dat);
void	print_stack(t_stack *st);
void	print_ops(t_data *dat);
void	print_stacks(t_data *dat);

void	_min_max(t_stack *st);


#endif