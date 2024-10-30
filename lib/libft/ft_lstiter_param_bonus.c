/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_param_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-18 12:52:07 by hbreeze           #+#    #+#             */
/*   Updated: 2024-10-18 12:52:07 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter_param_bonus(t_list *lst,
		void (*f)(t_list *, void *), void *param)
{
	t_list	*index;

	if (!lst || !f)
		return ;
	index = lst;
	while (index)
	{
		f(index->content, param);
		index = index->next;
	}
}
