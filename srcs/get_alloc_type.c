/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_alloc_type.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 19:40:41 by jjaniec           #+#    #+#             */
/*   Updated: 2019/10/19 22:38:03 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

extern t_malloc_header	*g_alloc_mem[3];

/*
** Calculate allocation type between:
** TINY / SMALL / BIG
** (also corresponding index of g_alloc_mem)
*/

int		get_alloc_type(size_t size)
{
	return (0 + (size > TINY_MAX_SIZE) + (size > SMALL_MAX_SIZE));
}
