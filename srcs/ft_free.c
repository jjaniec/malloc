/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 11:36:57 by jjaniec           #+#    #+#             */
/*   Updated: 2019/11/07 20:20:10 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

extern t_malloc_header *g_alloc_mem[3];

extern pthread_mutex_t g_lock;

/*
** Free allocation using data pointer
** & defragment memory page in free_alloc()
*/

static void		ft_free(void *ptr)
{
	t_malloc_header	*alloc_header;
	int				i;

	if (!ptr)
		return ;
	i = 0;
	alloc_header = get_alloc_header(ptr, &i);
	free_alloc(alloc_header, i);
}

void			free(void *ptr)
{
	pthread_mutex_lock(&g_lock);
	ft_free(ptr);
	pthread_mutex_unlock(&g_lock);
}
