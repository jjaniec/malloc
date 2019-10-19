/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_header.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 14:05:21 by jjaniec           #+#    #+#             */
/*   Updated: 2019/10/19 22:41:10 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

/*
** Write a t_malloc_header struct into a memory page defining an allocation
** returned by malloc() or realloc()
*/

void		write_header(void *ptr, bool free, size_t size, \
					t_malloc_header *prev, t_malloc_header *next)
{
	((t_malloc_header *)ptr)->free = free;
	((t_malloc_header *)ptr)->size = size;
	((t_malloc_header *)ptr)->prev = prev;
	((t_malloc_header *)ptr)->next = next;
}
