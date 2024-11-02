/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-01 15:36:04 by hbreeze           #+#    #+#             */
/*   Updated: 2024-11-01 15:36:04 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input_handler.h"

int	create_int_lst(t_list **lst, int argc, char **argv)
{
	char	**split;
	int		index;

	if (!argc || !argv || !*argv)
		return (0);
	index = 0;
	while (index < argc)
	{
		split = ft_split(argv[index], ' ');
		if (!split)
			break ;
		if (!list_add_back(lst, split))
			break ;
		index++;
	}
	if (index != argc)
	{
		p_cleanup(lst, 0, split);
		return (0);
	}
	return (1);
}

int	str_gt(char *s1, char *s2)
{
	size_t i;

	i = 0;
	while (s1[i])
	{
		if (s1[i] == '-' && ++i)
			continue ;
		if (s1[i] > s2[i])
			return (1);
		else if (s1[i] < s2[i])
			return (0);
		i++;
	}
	return (0);
}

int	set_int_or_err(char *str, int *output)
{
	size_t comp;
	size_t test;

	if (str[0] == '-')
	{
		comp = ft_strlen(INT_MIN_STR);
		test = ft_strlen(str);
		if (test > comp || (test == comp && str_gt(str, INT_MIN_STR))
			|| (test == 1))
			return (0);
	}
	else
	{
		if (str[0] == '+')
			 str = &(str[1]);
		comp = ft_strlen(INT_MAX_STR);
		test = ft_strlen(str);
		if (test > comp || (test == comp && str_gt(str, INT_MAX_STR))
			|| (test == 0))
			return (0);
	}
	*output = ft_atoi(str);
	return (1);
}

int	lst_to_arr(t_list *lst, int **output)
{
	t_list	*iter;
	size_t	tmp;
	size_t	index;

	index = 0;
	iter = lst;
	while (iter)
	{
		tmp = index;
		while(((char **)iter->content)[index - tmp])
		{
			if (!set_int_or_err(((char **)iter->content)[index - tmp], &((*output)[index])))
				return (0);
			index++;
		}
		iter = iter->next;
	}
	return (1);
}

size_t	parse_input(int argc, char **argv, int **output)
{
	t_list	*lst;
	t_list	*index;
	size_t	count;

	if (!create_int_lst(&lst, argc, argv))
		return (0);
	index = lst;
	while (index)
	{
		count += arr_size(index->content);
		index = index->next;
	}
	if (!count)
	{
		p_cleanup(&lst, 0, 0);
		return (0);
	}
	*output = zeroit(malloc(count * sizeof(int)), count * sizeof(int));
	if (!lst_to_arr(lst, output))
	{
		p_cleanup(&lst, output, 0);
		return (0);
	}
	p_cleanup(&lst, 0, 0);
	return (count);
}
