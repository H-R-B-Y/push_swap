/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-01 16:11:15 by hbreeze           #+#    #+#             */
/*   Updated: 2024-11-01 16:11:15 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input_handler.h"

void _ft_split_cleanup(void *str)
{
	char	**tmp;
	size_t	s;

	if (!str)
		return ;
	s = 0;
	tmp = (char **)str;
	while(tmp[s])
		free(tmp[s++]);
	free(str);
}

size_t	arr_size(void **arr)
{
	size_t	s;

	s = 0;
	while (arr[s])
		s++;
	return (s);
}

void	p_cleanup(t_list **lst, int **arr, char **str)
{
	if (lst)
		ft_lstclear(lst, _ft_split_cleanup);
	if (arr)
		free(*arr);
	if (str)
		_ft_split_cleanup(str);
}

int list_add_back(t_list **lst, void *content)
{
	t_list	*tmp;

	if (!lst || !content)
		return (0);
	tmp = ft_lstnew(content);
	if (!tmp)
		return (0);
	ft_lstadd_back(lst, tmp);
	return (1);
}
