/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 11:36:57 by jjaniec           #+#    #+#             */
/*   Updated: 2019/10/10 00:14:45 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

extern t_malloc_header *g_alloc_mem[3];

void 					free(void *ptr)
{
	t_malloc_header		*alloc_header;
	int					i;


	// ft_putstr("Free - ");
	// ft_putnbr((unsigned long) ptr);
	// ft_putchar('\n');

	if (!ptr)
		return ;
	i = 0;
	alloc_header = get_alloc_header(ptr, &i);
	free_alloc(alloc_header, i);
}
