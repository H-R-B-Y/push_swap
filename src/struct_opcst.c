/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_opcst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-31 12:29:33 by hbreeze           #+#    #+#             */
/*   Updated: 2024-10-31 12:29:33 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	append_ops(t_opc *cst, t_stack *st,
		t_op_code code, long long count)
{
	t_op_desc	*tmp;

	if (!cst || !st || !count)
		return (0);
	tmp = zeroit(malloc(sizeof(t_op_desc)), sizeof(t_op_desc));
	if (!tmp)
		return (0);
	ft_lstadd_back(&cst->ops, ft_lstnew(tmp));
	tmp->count = count;
	tmp->op = code;
	tmp->st = st;
	return (count);
}

t_opc	*create_cost(long long index)
{
	t_opc	*output; 

	output = zeroit(malloc(sizeof(t_opc)), sizeof(t_opc));
	if (!output)
		return (0);
	output->index = index;
	return (output);
}

void	destroy_cost(t_opc *cst)
{
	if (!cst)
		return ;
	if (cst->ops)
		ft_lstclear(&cst->ops, free);
	free(cst);
}
