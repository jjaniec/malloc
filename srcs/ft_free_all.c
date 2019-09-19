/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 19:33:53 by jjaniec           #+#    #+#             */
/*   Updated: 2019/09/19 23:51:47 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

extern t_malloc_header	*g_alloc_mem[3];

void		ft_free_all(void)
{
	int					i;
	t_malloc_header		*ptr;
	void				*tmp;

	i = -1;
	while (++i < 3)
	{
		printf("FT_FREE_ALL g_alloc_mem[%d] %p %p\n", i, g_alloc_mem[i], g_alloc_mem[i] + sizeof(t_malloc_header));
		while (1)
		{
			tmp = g_alloc_mem[i];
			if (!tmp)
				break ;
			printf("ft_free_all before free: g_alloc_mem[%d]: %p\n", i, tmp);
			ptr = tmp;
			while (ptr && ptr->free && ptr->next)
				ptr = ptr->next;
			ft_free(ptr + sizeof(t_malloc_header));
			printf("ft_free_all: after free: g_alloc_mem[%d]: %p\n", i, g_alloc_mem[i]);
		}
	}
}
