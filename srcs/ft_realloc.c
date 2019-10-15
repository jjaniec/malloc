/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 11:39:01 by jjaniec           #+#    #+#             */
/*   Updated: 2019/10/15 12:13:44 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

extern t_malloc_header *g_alloc_mem[3];

static void write_header(void *ptr, bool free, size_t size, t_malloc_header *prev, t_malloc_header *next)
{
	((t_malloc_header *)ptr)->free = free;
	((t_malloc_header *)ptr)->size = size;
	((t_malloc_header *)ptr)->prev = prev;
	((t_malloc_header *)ptr)->next = next;
}

static void *resize_alloc(t_malloc_header *alloc, size_t new_size, size_t headersize)
{
	size_t alloc_cur_size;
	void *r;

	r = NULL;
	alloc_cur_size = alloc->size;
	if (alloc_cur_size == new_size)
		return alloc;
	if (new_size < alloc_cur_size)
	{
		if (new_size + headersize >= alloc_cur_size)
			return alloc;
		if (alloc->next)
			alloc->next->prev = alloc + headersize + new_size;
		write_header(alloc + headersize + new_size, true, alloc->size - headersize - new_size, alloc, alloc->next);
		write_header(alloc, false, new_size, alloc->prev, alloc->next);
		r = alloc;
	}
	return (r);
}

void *realloc(void *ptr, size_t size)
{
	t_malloc_header *alloc_header;
	int				old_alloc_type;
	int				new_alloc_type;
	void			*r;
	int				i;

	ft_putstr("Realloc new size: ");
	ft_putnbr(size);
	ft_putchar('\n');
	while (size % 16)
		size++;
	new_alloc_type = 0 + (size > TINY_MAX_SIZE) + (size > SMALL_MAX_SIZE);
	if (!ptr)
		return malloc(size);
	if (ptr && !size)
	{
		free(ptr);
		return (NULL);
	}
	// if (!(alloc))
	// {
	// 	ft_putstr("Oopsie 1 - type: ");
	// 	ft_putnbr(alloc_type);
	// 	ft_putstr("\n");
	// 	return NULL;
	// }
	// if ((r = resize_alloc(alloc, size, sizeof(t_malloc_header))))
	// 	return r + sizeof(t_malloc_header);
	i = 0;
	alloc_header = get_alloc_header(ptr, &i);
	if (alloc_header)
	{
		ft_putstr("Realloc old size: ");
		ft_putnbr(alloc_header->size);
		ft_putstr("\n");
	}
	if ((r = malloc(size)) && alloc_header)
	{
		old_alloc_type = 0 + (alloc_header->size > TINY_MAX_SIZE) + (alloc_header->size > SMALL_MAX_SIZE);
		ft_memcpy(r, ptr, alloc_header->size);
		// if (new_alloc_type == old_alloc_type)
		// {
		// 	if (alloc_header->next)
		// 		alloc_header->next->prev = r - sizeof(t_malloc_header);
		// 	if (alloc_header->prev)
		// 		alloc_header->prev->next = r - sizeof(t_malloc_header);
		// }
		free_alloc(alloc_header, i);
	}
	return r;
}
