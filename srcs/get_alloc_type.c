/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_alloc_type.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 19:40:41 by jjaniec           #+#    #+#             */
/*   Updated: 2019/09/19 22:38:22 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

extern t_malloc_header	*g_alloc_mem[3];

int		get_alloc_type(t_malloc_header *alloc_header, size_t pagesize, size_t headersize)
{
	return (
		0 \
		+ (alloc_header->size > (pagesize * TINY_PAGE_SIZE - headersize)) \
		+ (alloc_header->size > (pagesize * SMALL_PAGE_SIZE - headersize))
	);
}
