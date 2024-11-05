/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dbg_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-29 15:38:18 by hbreeze           #+#    #+#             */
/*   Updated: 2024-10-29 15:38:18 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	print_state(t_data *dat)
{
	if (!dat)
		return ;
	ft_printf("----------------------\n");
	ft_printf("# Ops:	%10d\n", ft_lstsize(dat->ops_head));
	ft_printf("----------------------\n");
	ft_printf("# in A:	%10d\n", dat->a->top + 1);
	print_stack(dat->a);
	ft_printf("----------------------\n");
	ft_printf("# in B:	%10d\n", dat->b->top + 1);
	print_stack(dat->b);
	ft_printf("----------------------\n");
	print_ops(dat);
	ft_printf("----------------------\n\n");

}

void	print_stack(t_stack *st)
{
	long long index;

	if (!st)
		return ;
	index = 0;
	while (index <= st->top)
	{
		ft_printf("%d", st->items[index]);
		if (index != st->top)
			ft_putstr_fd(" ", 1);
		index++;
	}
	ft_putendl_fd("", 1);
}

static void	_print_wrapper(void *d)
{
	if (!d)
		return ;
	ft_printf("%s ", (char *)d);
}

void	print_ops(t_data *dat)
{
	if (!dat)
		return ;
	ft_lstiter(dat->ops_head, _print_wrapper);
	ft_putendl_fd("", 1);
}

# include <unistd.h>
void print_stacks(t_data *dat)
{
	long long i;

	i = dat->max_size;
	ft_printf("--------------------------------------\n");
	while (i >= 0)
	{
		if (i > dat->a->top && i > dat->b->top && i--)
		{
			ft_printf("		|		\n");
			continue ;
		}
		if (i <= dat->a->top)
			ft_printf("%d		|", dat->a->items[i]);
		else
			ft_printf("		|");
		if (i <= dat->b->top)
			ft_printf("		%d", dat->b->items[i]);
		else
			ft_printf("		");
		ft_printf("\n");
		i--;
	}
	ft_printf("--------------------------------------\n");
	ft_printf("A		|		B\n");
	usleep(100000);
}
