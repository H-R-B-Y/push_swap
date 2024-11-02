/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-29 15:38:34 by hbreeze           #+#    #+#             */
/*   Updated: 2024-10-29 15:38:34 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "push_swap.h"

static void	set_funcs(t_stack *a, t_stack *b)
{
	a->ops[SWAP] = swap_a;
	a->ops[PUSH] = push_b;
	a->ops[ROT] = rot_a;
	a->ops[REV] = rev_a;
	a->ops[RR] = rot_rot;
	a->ops[RRR] = rev_rev;
	b->ops[SWAP] = swap_b;
	b->ops[PUSH] = push_a;
	b->ops[ROT] = rot_b;
	b->ops[REV] = rev_b;
	b->ops[RR] = rot_rot;
	b->ops[RRR] = rev_rev;
}

t_data *init_data(size_t max_size)
{
	t_data *dat;

	dat = zeroit(malloc(sizeof(t_data)), sizeof(t_data));
	if (!dat)
		return (0);
	dat->max_size = max_size;
	dat->a = init_stack(max_size);
	dat->a->meta = dat;
	dat->a->max_size = &dat->max_size;
	dat->b = init_stack(max_size);
	dat->b->meta = dat;
	dat->b->max_size = &dat->max_size;
	dat->ops_head = 0;
	set_funcs(dat->a, dat->b);
	return (dat);
}

void	destory_data(t_data *dat)
{
	if (!dat)
		return ;
	if (dat->a)
		destroy_stack(dat->a);
	if (dat->b)
		destroy_stack(dat->b);
	if (dat->ops_head)
		ft_lstclear(&dat->ops_head, free);
	free(dat);
}
