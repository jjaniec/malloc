/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_alloc_header.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 21:37:02 by jjaniec           #+#    #+#             */
/*   Updated: 2019/10/17 22:59:31 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

extern t_malloc_header *g_alloc_mem[3];

static t_malloc_header		*cmp_alloc_list(void *ptr, t_malloc_header *start, \
								size_t headersize)
{
	while (start)
	{
		if ((void *)start + headersize == ptr)
			return (start);
		start = start->next;
	}
	return (NULL);
}

t_malloc_header				*get_alloc_header(void *ptr, int *alloc_mem_index)
{
	t_malloc_header *alloc_header;

	if (!ptr)
		return (NULL);
	alloc_header = NULL;
	while (!alloc_header && (*alloc_mem_index) < 3)
	{
		alloc_header = cmp_alloc_list(ptr, \
			g_alloc_mem[*alloc_mem_index], sizeof(t_malloc_header));
		if (!alloc_header)
			*(alloc_mem_index) += 1;
	}
	// if (!alloc_header)
	// {
		// ft_putstr_fd("get_alloc_header: 0x", 2);
		// ft_putnbr_base((unsigned int)ptr, 16);
		// ft_putstr_fd("not found\n", 2);
		// show_alloc_mem();
	// }
	return (alloc_header);
}
