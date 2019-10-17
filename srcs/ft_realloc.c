/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 11:39:01 by jjaniec           #+#    #+#             */
/*   Updated: 2019/10/17 14:28:50 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

extern t_malloc_header *g_alloc_mem[3];

static void		reduce_alloc(t_malloc_header *alloc, size_t new_size, \
					size_t headersize)
{
	t_malloc_header	*tmp;
	size_t			next_old_size;

	if (alloc->next && (tmp = alloc->next->next))
		tmp->prev = (void *)alloc + new_size + headersize;
	if (alloc->next)
	{
		next_old_size = alloc->next->size;
		alloc->next = (void *)alloc + new_size + headersize;
		write_header(alloc->next, true, \
			next_old_size + (alloc->size - new_size), alloc, tmp);
		alloc->size = new_size;
	}
}

static void		*resize_alloc(t_malloc_header *alloc, size_t new_size, \
					size_t headersize)
{
	size_t		alloc_cur_size;
	void		*r;

	r = NULL;
	alloc_cur_size = alloc->size;
	if (alloc_cur_size == new_size)
		return (alloc);
	if (new_size < alloc_cur_size)
	{
		if (alloc_cur_size - new_size < headersize)
			return (alloc);
		reduce_alloc(alloc, new_size, headersize);
		r = alloc;
	}
	return (r);
}

void			*realloc(void *ptr, size_t size)
{
	t_malloc_header *alloc_header;
	int				old_alloc_type;
	int				new_alloc_type;
	void			*r;
	int				i;

	r = NULL;
	while (size % 16)
		size++;
	if (!ptr)
		return (malloc(size));
	i = 0;
	alloc_header = get_alloc_header(ptr, &i);
	new_alloc_type = get_alloc_type(size);
	if (alloc_header && \
		(old_alloc_type = get_alloc_type(alloc_header->size)) == \
			new_alloc_type && \
		(r = resize_alloc(alloc_header, size, sizeof(t_malloc_header))))
		return (r + sizeof(t_malloc_header));
	if (alloc_header && (r = malloc(size)))
	{
		ft_memcpy(r, ptr, alloc_header->size);
		free_alloc(alloc_header, i);
	}
	return (r);
}
