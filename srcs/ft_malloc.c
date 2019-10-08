/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 17:46:38 by jjaniec           #+#    #+#             */
/*   Updated: 2019/10/08 15:59:46 by jjaniec          ###   ########.fr       */
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
}

static t_malloc_header	*append_page_to_list(size_t size, size_t headersize, int g_alloc_mem_index)
{
	void			*page;

	errno = 0;
	if ((page = mmap(NULL, size, PAGE_MMAP_PROT, PAGE_MMAP_FLAGS, 0, 0)) == MAP_FAILED)
		return NULL;
	write_header(page, (size > SMALL_MAX_SIZE) ? false : true, size - headersize, NULL, \
		g_alloc_mem[g_alloc_mem_index]);
	if (g_alloc_mem[g_alloc_mem_index])
		((t_malloc_header *)page)->next->prev = page;
	g_alloc_mem[g_alloc_mem_index] = page;
	return page;
}

static void 	*reserve_page_mem(size_t size, size_t headersize, int alloc_type)
{
	t_malloc_header	*cur_pos;

	if (!g_alloc_mem[alloc_type])
		return NULL;
	cur_pos = (t_malloc_header *)g_alloc_mem[alloc_type];
	while (cur_pos)
	{
		if (cur_pos->free == true && \
			cur_pos->size > headersize + size)
		{
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
	size_t	headersize;
	void	*addr;
	int		alloc_type;
	void	*page;

	pagesize = getpagesize();
	headersize = sizeof(t_malloc_header);
	alloc_type = 0 + (size > TINY_MAX_SIZE) + (size > SMALL_MAX_SIZE);
	if (size <= SMALL_MAX_SIZE && (addr = reserve_page_mem(size, headersize, alloc_type)))
		return addr;
	if (size <= TINY_MAX_SIZE)
		size = pagesize * TINY_PAGE_SIZE;
	else
		size = (size <= SMALL_MAX_SIZE) ? (pagesize * SMALL_PAGE_SIZE) : (size + headersize);
	if (!(page = append_page_to_list(size, headersize, alloc_type)))
		return NULL;
	if (size > SMALL_MAX_SIZE)
		return page + headersize;
	if (size <= SMALL_MAX_SIZE && (addr = reserve_page_mem(size, headersize, alloc_type)))
		return addr;
	return NULL;
}
