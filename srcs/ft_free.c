/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 11:36:57 by jjaniec           #+#    #+#             */
/*   Updated: 2019/10/19 22:29:12 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>
#include <signal.h>

extern t_malloc_header *g_alloc_mem[3];

/*
** Free allocation using data pointer
** & defragment memory page in free_alloc()
*/

void		free(void *ptr)
{
	t_malloc_header	*alloc_header;
	int				i;

	if (!ptr)
		return ;
	i = 0;
	alloc_header = get_alloc_header(ptr, &i);
	free_alloc(alloc_header, i);
}
