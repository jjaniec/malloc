/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 17:46:38 by eparisot          #+#    #+#             */
/*   Updated: 2019/08/26 20:26:27 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

void *ft_malloc(size_t size)
{
	printf("requested malloc of size : %zu\n", size);
	size_t pagesize;
	void *addr;

	pagesize = getpagesize();
	addr = mmap(NULL, pagesize, PROT_READ | PROT_WRITE | PROT_EXEC,
				MAP_ANON | MAP_PRIVATE, 0, 0);
	if (addr == MAP_FAILED)
		return NULL;
	printf("pagesize : %zu\n", pagesize);
	printf("mallocated %zu at %p\n", size, addr);
	return addr;
}
