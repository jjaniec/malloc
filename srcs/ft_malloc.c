/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 17:46:38 by jjaniec           #+#    #+#             */
/*   Updated: 2019/10/17 23:10:14 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

t_malloc_header *g_alloc_mem[3] = {NULL, NULL, NULL};

static t_malloc_header	*append_page_to_list(size_t size, size_t headersize, \
							int g_alloc_mem_index)
{
	void	*page;
	size_t	newpage_size;

	errno = 0;
	newpage_size = 0;
	if (g_alloc_mem_index == 2)
		newpage_size = size + headersize;
	else
		newpage_size = getpagesize() * \
			((g_alloc_mem_index == 0) ? (TINY_PAGE_SIZE) : (SMALL_PAGE_SIZE));
	if ((page = mmap(NULL, newpage_size, \
		PAGE_MMAP_PROT, PAGE_MMAP_FLAGS, 0, 0)) == MAP_FAILED)
	{
		ft_putstr_fd("Malloc: mmap returned an error\n", 2);
		return (NULL);
	}
	write_header(page, \
		(g_alloc_mem_index == 2) ? (false) : (true), \
		newpage_size - headersize, NULL, g_alloc_mem[g_alloc_mem_index]);
	if (g_alloc_mem[g_alloc_mem_index])
		((t_malloc_header *)page)->next->prev = page;
	g_alloc_mem[g_alloc_mem_index] = page;
	return (page);
}

static void				*reserve_page_mem(size_t size, size_t headersize, \
							int alloc_type)
{
	t_malloc_header *cur_pos;

	if (!g_alloc_mem[alloc_type])
		return (NULL);
	cur_pos = (t_malloc_header *)g_alloc_mem[alloc_type];
	while (cur_pos)
	{
		if (cur_pos->free == true &&
			cur_pos->size > headersize + size)
		{
			write_header((void *)cur_pos + headersize + size, true, \
				cur_pos->size - size - headersize, cur_pos, cur_pos->next);
			write_header((void *)cur_pos, false, size, \
				cur_pos->prev, (void *)cur_pos + headersize + size);
			if (cur_pos->next && cur_pos->next->next) //
				cur_pos->next->next->prev = cur_pos->next; //
			return (void *)cur_pos + headersize;
		}
		cur_pos = cur_pos->next;
	}
	return (NULL);
}

void					*malloc(size_t size)
{
	size_t		headersize;
	void		*addr;
	int			alloc_type;
	void		*page;

	while (size % 16)
		size++;
	if ((alloc_type = get_alloc_type(size)) > 2)
		return (NULL);
	headersize = sizeof(t_malloc_header);
	if (alloc_type < 2 && \
		(addr = reserve_page_mem(size, headersize, alloc_type)))
		return (addr);
	if (!(page = append_page_to_list(size, headersize, alloc_type)))
		return (NULL);
	if (alloc_type == 2)
		return (page + headersize);
	addr = reserve_page_mem(size, headersize, alloc_type);
	return (addr);
}
