/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_alloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 11:36:57 by jjaniec           #+#    #+#             */
/*   Updated: 2019/10/19 22:46:50 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

extern t_malloc_header *g_alloc_mem[3];

/*
** Returns 1 if two headers are next to each other
** and on the same mmap() page,
** otherwise return 0
*/

static int	follows_on_same_page(t_malloc_header *ptr, t_malloc_header *ptr2, size_t pagesize)
{
	if (!(ptr && ptr2 && ptr->next) ||
		sizeof(t_malloc_header) + ptr->size == \
			pagesize * TINY_PAGE_SIZE ||
		sizeof(t_malloc_header) + ptr->size == \
			pagesize * SMALL_PAGE_SIZE)
		return (0);
	return (((void *)ptr + ptr->size + sizeof(t_malloc_header) == \
		(void *)ptr2));
}

static int	unmap_page(t_malloc_header *start_header, int alloc_type)
{
	int	r;

	if (start_header->prev)
		start_header->prev->next = start_header->next;
	if (start_header->next)
		start_header->next->prev = start_header->prev;
	if (g_alloc_mem[alloc_type] == start_header)
		g_alloc_mem[alloc_type] = \
			start_header->prev ? start_header->prev : start_header->next;
	if ((r = munmap((void *)start_header, \
		(unsigned int)start_header->size + sizeof(t_malloc_header))))
		ft_putstr_fd("Free: munmap returned an error\n", 2);
	return (r);
}

/*
** Merge 2 freed allocations
*/

static void	merge_allocs(t_malloc_header *alloc, t_malloc_header *merged_alloc)
{
	alloc->size += merged_alloc->size + sizeof(t_malloc_header);
	alloc->next = merged_alloc->next;
	if (alloc->next)
		alloc->next->prev = alloc;
}

/*
** Merge all freed allocations next to each other
** in memory pages
*/

static void	defrag(t_malloc_header *start, size_t pagesize, \
				size_t headersize, int alloc_type)
{
	if (start && start->free == true)
	{
		if (alloc_type != 2)
		{
			while (start->prev && start->prev->free && follows_on_same_page(start->prev, start, pagesize))
				start = start->prev;
			while (start->next && start->next->free && follows_on_same_page(start, start->next, pagesize))
				merge_allocs(start, start->next);
		}
		if (alloc_type == 2 ||
			((start->size + headersize == pagesize * TINY_PAGE_SIZE ||
			start->size + headersize == pagesize * SMALL_PAGE_SIZE) /*&& \
			(start->next || start->prev)*/))
			unmap_page(start, alloc_type);
	}
}

/*
** Free allocation passed as parameter
*/

void		free_alloc(t_malloc_header *alloc_header, int alloc_mem_index)
{
	if (!alloc_header)
		return ;
	alloc_header->free = true;
	defrag(alloc_header, getpagesize(), \
		sizeof(t_malloc_header), alloc_mem_index);
}
