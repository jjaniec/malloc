/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 22:07:15 by jjaniec           #+#    #+#             */
/*   Updated: 2019/10/08 15:52:53 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

void		*ft_calloc(size_t nmemb, size_t size)
{
	void 	*ptr;

	if (nmemb == 0 || size == 0 || SIZE_MAX / nmemb <= size)
		return NULL;
	if ((ptr = ft_malloc(nmemb * size)))
		ft_bzero(ptr, nmemb * size);
	return ptr;
}
