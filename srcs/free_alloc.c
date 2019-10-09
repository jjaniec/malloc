/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_alloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 11:36:57 by jjaniec           #+#    #+#             */
/*   Updated: 2019/10/10 00:15:23 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

extern t_malloc_header *g_alloc_mem[3];

/*
** Returns 1 if two headers are not next to each other and on the same mmap() page,
** otherwise return 0
*/

static int				follows_on_same_page(t_malloc_header *ptr, t_malloc_header *ptr2)
{
	if (!(ptr && ptr2 && ptr->next) || \
		sizeof(t_malloc_header) + ptr->size == (long unsigned int)getpagesize() * TINY_PAGE_SIZE || \
		sizeof(t_malloc_header) + ptr->size == (long unsigned int)getpagesize() * SMALL_PAGE_SIZE)
		return 1;
	return (!(ptr + ptr->size + sizeof(t_malloc_header) == ptr2));
}

static int				unmap_page(t_malloc_header *start_header, size_t pagesize, size_t headersize, int alloc_type)
{
	if (start_header->prev)
		start_header->prev->next = start_header->next;
	if (start_header->next)
		start_header->next->prev = start_header->prev;
	if (g_alloc_mem[alloc_type] == start_header)
		g_alloc_mem[alloc_type] = start_header->prev ? start_header->prev : start_header->next;
	return munmap(start_header, start_header->size);
}

static void		defrag(t_malloc_header *start, size_t pagesize, size_t headersize, int alloc_type)
{
	if (start && start->free == true)
	{
		if (start->prev && start->prev->free == true && \
			!follows_on_same_page(start->prev, start))
			return defrag(start->prev, pagesize, headersize, alloc_type);
		while (start->next && start->next->free == true && \
			!follows_on_same_page(start, start->next))
		{
			start->size += start->next->size + headersize;
			start->next = start->next->next;
			if (start->next)
				start->next->prev = start;
		}
		if (alloc_type == 2 || \
			start->size == pagesize * TINY_PAGE_SIZE - headersize || \
			start->size == pagesize * SMALL_PAGE_SIZE - headersize)
			unmap_page(start, pagesize, headersize, alloc_type);
		return ;
	}
}

void 					free_alloc(t_malloc_header *alloc_header, int alloc_mem_index)
{
	if (!alloc_header)
		return ;
	// ft_putstr("Free_alloc size: ");
	// ft_putnbr(alloc_header->size);
	// ft_putstr("\n");
	alloc_header->free = true;
	// if (alloc_mem_index == -1)
		// alloc_mem_index = 
	defrag(alloc_header, getpagesize(), sizeof(t_malloc_header), alloc_mem_index);
}
