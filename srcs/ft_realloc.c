/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 11:39:01 by jjaniec           #+#    #+#             */
/*   Updated: 2019/10/19 22:35:48 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

extern t_malloc_header *g_alloc_mem[3];

/*
** Update current block size &
** create a new next block equals to
** freed_size * sizeof(t_malloc_header)
*/

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

/*
** Resize given allocation
*/

static void		*resize_alloc(t_malloc_header *alloc, size_t new_size, \
					size_t headersize)
{
	size_t		alloc_cur_size;

	alloc_cur_size = alloc->size;
	if (alloc_cur_size == new_size)
		return ((void *)alloc);
	if (new_size < alloc_cur_size)
	{
		if (alloc_cur_size - new_size < headersize)
			return (alloc);
		reduce_alloc(alloc, new_size, headersize);
		return ((void *)alloc);
	}
	return (NULL);
}

/*
** Copy data of old block into the new one before free'ing the old block
*/

static void		replace_block(void *new_block, t_malloc_header *alloc_header, \
					size_t size, int alloc_type)
{
	ft_memcpy(new_block, (void *)alloc_header + sizeof(t_malloc_header), \
		(alloc_header->size > size) ? (size) : (alloc_header->size));
	free_alloc(alloc_header, alloc_type);
}

/*
** Reallocate given ptr with a new size and return NULL if it fails
*/

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
	i = 0;
	if (!ptr)
		return (malloc(size));
	alloc_header = get_alloc_header(ptr, &i);
	new_alloc_type = get_alloc_type(size);
	if (alloc_header)
		old_alloc_type = get_alloc_type(alloc_header->size);
	if (alloc_header && alloc_header->next && alloc_header->next->free && \
		old_alloc_type < 2 && \
		old_alloc_type == new_alloc_type && \
		(r = resize_alloc(alloc_header, size, sizeof(t_malloc_header))))
		return ((void *)r + sizeof(t_malloc_header));
	if (alloc_header && (r = malloc(size)))
		replace_block(r, alloc_header, size, i);
	return (r);
}
