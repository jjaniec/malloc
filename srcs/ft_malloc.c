/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 17:46:38 by jjaniec           #+#    #+#             */
/*   Updated: 2019/09/16 16:06:03 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

void *g_alloc_mem[2] = {NULL, NULL};

static void		write_header(void *ptr, bool freed, unsigned int size, t_malloc_header *prev, t_malloc_header *next)
{
	((t_malloc_header *)ptr)->freed = freed;
	((t_malloc_header *)ptr)->size = size;
	((t_malloc_header *)ptr)->prev = prev;
	((t_malloc_header *)ptr)->next = next;

	printf("Write new header @%p, size: %u, prev addr: %p\n", ptr, ((t_malloc_header *)ptr)->size, ((t_malloc_header *)ptr)->prev);
}

static int		init_page_region(int count, size_t pagesize, size_t header_size, int g_alloc_mem_index)
{
	void	*prev_page_addr;
	void	*page;
	int		i;

	i = 0;
	prev_page_addr = NULL;
	while (i++ < count)
	{
		if ((page = mmap(NULL, pagesize, PAGE_MMAP_PROT, PAGE_MMAP_FLAGS, 0, 0)) == MAP_FAILED)
			return 1;
		write_header(page, true, pagesize - header_size, prev_page_addr, NULL);
		if (prev_page_addr)
			((t_malloc_header *)prev_page_addr)->next = page;
		else
			g_alloc_mem[g_alloc_mem_index] = page;
		prev_page_addr = page;
	}
	return 0;
}

static int 		init_alloc_mem(size_t pagesize)
{
	init_page_region(TINY_REGION_PAGE_COUNT, pagesize, sizeof(t_malloc_header), 0);
	init_page_region(SMALL_REGION_PAGE_COUNT, pagesize, sizeof(t_malloc_header), 1);
	return 0;
}

static void 	*reserve_page_mem(size_t size)
{
	void			*page;
	t_malloc_header	*cur_pos;

	page = g_alloc_mem[size > TINY_MAX_SIZE];
	cur_pos = (t_malloc_header *)page;
	while (cur_pos)
	{
		printf("Allocation %p - size %u - prev: %p - next: %p\n", cur_pos, cur_pos->size, cur_pos->prev, cur_pos->next);
		if (cur_pos->freed == true && \
			cur_pos->size > sizeof(t_malloc_header) + size)
		{
			cur_pos->freed = false;
			cur_pos->next = cur_pos + size;
			write_header(cur_pos + size, false, cur_pos->size - size - sizeof(t_malloc_header), cur_pos, NULL);
			cur_pos->size = size;
			return cur_pos + sizeof(t_malloc_header);
		}
		cur_pos = cur_pos->next;
	}
	return NULL;
}

void			*ft_malloc(size_t size)
{
	size_t pagesize;
	void *addr;

	printf("requested malloc of size : %zu\n", size);
	pagesize = getpagesize();
	printf("Pagesize: %zu\n", pagesize);
	printf("header struct size: %zu\n", sizeof(t_malloc_header));
	if (size < SMALL_MAX_SIZE)
	{
		if (!(g_alloc_mem[0]) && init_alloc_mem(pagesize))
			return NULL;
		return reserve_page_mem(size);
	}
	else
		if ((addr = mmap(NULL, pagesize, PAGE_MMAP_PROT, PAGE_MMAP_FLAGS, 0, 0)) \
			== MAP_FAILED)
			return NULL;
	printf("mallocated %zu at %p\n", size, addr);
	return addr;
}
