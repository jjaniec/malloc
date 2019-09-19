/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 11:36:57 by jjaniec           #+#    #+#             */
/*   Updated: 2019/09/19 20:02:35 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

extern t_malloc_header *g_alloc_mem[2];

/*
** Returns 1 if two headers are not next to each other and on the same mmap() page,
** otherwise return 0
*/

static int				follows_on_same_page(t_malloc_header *ptr, t_malloc_header *ptr2)
{
	if (!(ptr && ptr2 && ptr->next) || \
		sizeof(t_malloc_header) + ptr->size == getpagesize() * TINY_PAGE_SIZE || \
		sizeof(t_malloc_header) + ptr->size == getpagesize() * SMALL_PAGE_SIZE)
		return 1;
	return (!(ptr + ptr->size + sizeof(t_malloc_header) == ptr2));
}

static t_malloc_header	*search_alloc_header(void *ptr, t_malloc_header *start)
{
	// return ptr - sizeof(t_malloc_header);
	while (start)
	{
		printf("Search %p - %p - eq: %d\n", ptr, start + sizeof(t_malloc_header), start + sizeof(t_malloc_header) == ptr);
		if (start + sizeof(t_malloc_header) == ptr)
			return start;
		start = start->next;
	}
	return NULL;
}

static int				unmap_page(t_malloc_header *start_header, size_t pagesize, size_t headersize)
{
	int		alloc_type;

	if (start_header->prev)
		start_header->prev->next = start_header->next;
	if (start_header->next)
		start_header->next->prev = start_header->prev;
	alloc_type = get_alloc_type(start_header, pagesize, headersize);
	printf("Unmap %p size: %u alloc_mem start header: %p\n", start_header, start_header->size, g_alloc_mem[alloc_type]);
	if (g_alloc_mem[alloc_type] == start_header)
	{
		g_alloc_mem[alloc_type] = start_header->prev ? start_header->prev : start_header->next;
		printf("Updated header %d to %p\n", alloc_type, g_alloc_mem[alloc_type]);
	}
	return munmap(start_header, start_header->size);
}

static void		defrag(t_malloc_header *start, size_t pagesize, size_t headersize)
{
	if (start && start->free == true)
	{
		if (start->prev && start->prev->free == true && \
			!follows_on_same_page(start->prev, start))
			return defrag(start->prev, pagesize, headersize);
		while (start->next && start->next->free == true && \
			!follows_on_same_page(start, start->next))
		{
			start->size += start->next->size + headersize;
			start->next = start->next->next;
			if (start->next)
				start->next->prev = start;
		}
		if (start->size == pagesize * TINY_PAGE_SIZE - headersize || \
			start->size == pagesize * SMALL_PAGE_SIZE - headersize)
			unmap_page(start, pagesize, headersize);
		return ;
	}
}

void 					ft_free(void *ptr)
{
	t_malloc_header		*alloc_header;
	size_t				pagesize;
	size_t				headersize;

	if (!ptr)
		return ;
	printf("g_mem_alloc[0]: %p - [1]: %p\n", g_alloc_mem[0], g_alloc_mem[1]);
	pagesize = getpagesize();
	headersize = sizeof(t_malloc_header);
	alloc_header = search_alloc_header(ptr, g_alloc_mem[0]);
	if (!alloc_header)
		alloc_header = search_alloc_header(ptr, g_alloc_mem[1]);
	if (alloc_header)
	{
		alloc_header->free = true;
		printf("Found block %p - free %d - size: %d - next: %p - prev: %p\n", ptr, alloc_header->free, alloc_header->size, alloc_header->next, alloc_header->prev);
		defrag(alloc_header, pagesize, headersize);
	}
}
