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

int main(void)
{
	t_data *dat;
	
	dat = init_data(21);
	push(dat->a, 9);
	push(dat->a, 0);
	push(dat->a, 8);
	push(dat->a, 7);
	push(dat->a, 1);
	push(dat->a, 6);
	push(dat->a, 4);
	push(dat->a, 5);
	push(dat->a, 3);
	push(dat->a, 10);
	push(dat->a, 2);
	push(dat->a, 9 + 10);
	push(dat->a, 8 + 10);
	push(dat->a, 7 + 10);
	push(dat->a, 1 + 10);
	push(dat->a, 6 + 10);
	push(dat->a, 4 + 10);
	push(dat->a, 5 + 10);
	push(dat->a, 3 + 10);
	push(dat->a, 10 + 10);
	push(dat->a, 2 + 10);
	do_sort(dat);
	print_ops(dat);
	destory_data(dat);
}
