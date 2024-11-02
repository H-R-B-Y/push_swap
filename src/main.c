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

int main(int argc, char **argv)
{
	t_data	*dat;
	int		*arr;
	size_t	count;

	count = parse_input(argc - 1, &(argv[1]), &arr);
	dat = init_data(count);
	free(dat->a->items);
	dat->a->items = arr;
	dat->a->top = count - 1;
	do_sort(dat);
	print_ops(dat);
	destory_data(dat);
}
