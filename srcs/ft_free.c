/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 11:36:57 by jjaniec           #+#    #+#             */
/*   Updated: 2019/10/15 12:12:40 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

extern t_malloc_header *g_alloc_mem[3];

void free(void *ptr)
{
	t_malloc_header *alloc_header;
	int i;

	// printf("Free %p\n", ptr);
	ft_putstr("Free - 0x");
	ft_putnbr_base((unsigned long)ptr, 16);
	ft_putchar('\n');
	// show_alloc_mem();

	if (!ptr)
		return;
	i = 0;
	alloc_header = get_alloc_header(ptr, &i);
	if (!alloc_header)
		ft_putstr("Free: header not found\n");
	free_alloc(alloc_header, i);
}
