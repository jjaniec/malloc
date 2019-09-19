/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 19:33:53 by jjaniec           #+#    #+#             */
/*   Updated: 2019/09/19 15:19:47 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

extern t_malloc_header	*g_alloc_mem[2];

static void	free_alloc_list(void ***alloc_list_ptr)
{
	if (!(alloc_list_ptr && *alloc_list_ptr))
		return ;
	ft_free(*alloc_list_ptr + sizeof(t_malloc_header));
	free_alloc_list(alloc_list_ptr);
}

void		ft_free_all(void)
{
	int					i;
	t_malloc_header		*ptr;
	void				*tmp;

	i = -1;
	while (++i < 2)
	{
		printf("FT_FREE_ALL g_alloc_mem[%d] %p %p\n", i, g_alloc_mem[i], g_alloc_mem[i] + sizeof(t_malloc_header));
		while (1)
		{
			tmp = g_alloc_mem[i];
			if (!tmp)
				break ;
			printf("g_alloc_mem[%d]: %p\n", i, tmp);
			ptr = tmp;
			while (ptr && ptr->free && ptr->next)
				ptr = ptr->next;
			ft_free(ptr + sizeof(t_malloc_header));
		}
	}
}
