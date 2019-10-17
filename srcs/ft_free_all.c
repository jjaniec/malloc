/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 19:33:53 by jjaniec           #+#    #+#             */
/*   Updated: 2019/10/17 14:30:04 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

extern t_malloc_header *g_alloc_mem[3];

void		ft_free_all(void)
{
	t_malloc_header	*ptr;
	int				i;
	void			*tmp;

	i = -1;
	while (++i < 3)
	{
		while (1)
		{
			tmp = g_alloc_mem[i];
			if (!tmp)
				break ;
			ptr = tmp;
			while (ptr && ptr->free && ptr->next)
				ptr = ptr->next;
			free_alloc(ptr, i);
		}
	}
}
