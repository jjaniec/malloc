/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 17:46:38 by jjaniec           #+#    #+#             */
/*   Updated: 2019/09/19 23:29:48 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

t_malloc_header *g_alloc_mem[3] = {NULL, NULL, NULL};

static void				write_header(void *ptr, bool free, size_t size, t_malloc_header *prev, t_malloc_header *next)
{
	((t_malloc_header *)ptr)->free = free;
	((t_malloc_header *)ptr)->size = size;
	((t_malloc_header *)ptr)->prev = prev;
	((t_malloc_header *)ptr)->next = next;

	printf("Write new header @%p, free: %d, size: %zu, prev addr: %p - next addr: %p - alloc type: %d\n", \
		ptr, ((t_malloc_header *)ptr)->free, \
		((t_malloc_header *)ptr)->size, ((t_malloc_header *)ptr)->prev, ((t_malloc_header *)ptr)->next, \
		get_alloc_type(ptr, getpagesize(), sizeof(t_malloc_header)));
}

static t_malloc_header	*append_page_to_list(size_t size, size_t headersize, int g_alloc_mem_index)
{
	void			*page;
	t_malloc_header	*ptr;

	printf("MMAP %zu\n", size);
	errno = 0;
	if ((page = mmap(NULL, size, PAGE_MMAP_PROT, PAGE_MMAP_FLAGS, 0, 0)) == MAP_FAILED)
		return NULL;
	printf("MMAP Returned %p - errno %d\n", page, errno);
	ptr = g_alloc_mem[g_alloc_mem_index];
	if (!ptr)
		g_alloc_mem[g_alloc_mem_index] = page;
	else
	{
		while (ptr && ptr->next)
			ptr = ptr->next;
		ptr->next = page;
	}
	write_header(page, true, size - headersize, ptr, NULL);
	if (!ptr)
		printf("Initialized g_alloc_mem[%d] w/ page of size: %zu @%p\n", g_alloc_mem_index, size, g_alloc_mem[g_alloc_mem_index]);
	else
		printf("Appended new page to g_alloc_mem[%d] - size: %zu @%p\n", g_alloc_mem_index, ptr->size, ptr);
	return page;
}

static void 	*reserve_page_mem(size_t size, size_t headersize, int alloc_type)
{
	void			*page;
	t_malloc_header	*cur_pos;

	page = g_alloc_mem[alloc_type];
	cur_pos = (t_malloc_header *)page;
	while (cur_pos)
	{
		printf("Allocation %p - size %zu - free: %d - prev: %p - next: %p\n", cur_pos, cur_pos->size, cur_pos->free, cur_pos->prev, cur_pos->next);
		if (cur_pos->free == true && \
			cur_pos->size > headersize + size)
		{
			printf("Headersize: %zu - size + headersize: %zu - pointers %p %p\n", headersize, size + headersize, cur_pos, cur_pos + headersize + size);
			write_header((void *)cur_pos + headersize + size, true, cur_pos->size - size - headersize, cur_pos, cur_pos->next);
			write_header((void *)cur_pos, false, size, cur_pos->prev, cur_pos + headersize + size);
			return (void *)cur_pos + headersize;
		}
		cur_pos = cur_pos->next;
	}
	return NULL;
}

void			*ft_malloc(size_t size)
{
	size_t	pagesize;
	void	*addr;
	int		alloc_type;
	void	*page;
	size_t headersize;

	pagesize = getpagesize();
	headersize = sizeof(t_malloc_header);
	alloc_type = 0 + (size > TINY_MAX_SIZE) + (size > SMALL_MAX_SIZE);

	printf("requested malloc of size : %zu\n", size);
	printf("Pagesize: %zu - alloc_type: %d\n", pagesize, alloc_type);
	printf("header struct size: %zu\n", headersize);

	if (size <= SMALL_MAX_SIZE && (addr = reserve_page_mem(size, headersize, alloc_type)))
		return addr;
	if (size <= TINY_MAX_SIZE)
		size = pagesize * TINY_PAGE_SIZE;
	else if (size <= SMALL_MAX_SIZE)
		size = pagesize * SMALL_PAGE_SIZE;
	else
		size += headersize;
	if (!(page = append_page_to_list(size, headersize, alloc_type)))
		return NULL;
	if (size > SMALL_MAX_SIZE)
	{
		((t_malloc_header *)page)->free = false;
		return page + headersize;
	}
	if (size <= SMALL_MAX_SIZE && (addr = reserve_page_mem(size, headersize, alloc_type)))
		return addr;
	return NULL;
	// addr = page + headersize;
	// return addr;
}
