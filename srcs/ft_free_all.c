/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 19:33:53 by jjaniec           #+#    #+#             */
/*   Updated: 2019/10/14 16:39:51 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

extern t_malloc_header *g_alloc_mem[3];

void ft_free_all(void)
{
	int		i;
	void	*ptr;
	void	*tmp;

	// printf("FT FREE ALL %p - %p - %p\n", g_alloc_mem[0], g_alloc_mem[1], g_alloc_mem[2]);
	i = -1;
	while (++i < 3)
	{
		while (1)
		{
			tmp = g_alloc_mem[i];
			if (!tmp)
				break;
			ptr = tmp;
			while (ptr && ((t_malloc_header *)ptr)->free && ((t_malloc_header *)ptr)->next)
				ptr = ((t_malloc_header *)ptr)->next;
			free(ptr + sizeof(t_malloc_header));
			show_alloc_mem();
		}
	}
}
