/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-01 16:09:58 by hbreeze           #+#    #+#             */
/*   Updated: 2024-11-01 16:09:58 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_HANDLER_H
# define INPUT_HANDLER_H

# include "../../include/libft.h"
# include <stdlib.h>

# define INT_MAX_STR "2147483647"
# define INT_MIN_STR "-2147483648"

void	_ft_split_cleanup(void *str);

size_t	arr_size(void **arr);

void	p_cleanup(t_list **lst, int **arr, char **str);

int		list_add_back(t_list **lst, void *content);

int		lst_to_arr(t_list *lst, int **output);

size_t	parse_input(int argc, char **argv, int **output);

int		set_int_or_err(char *str, int *output);

int		str_gt(char *s1, char *s2);

int		create_int_lst(t_list **lst, int argc, char **argv);

#endif