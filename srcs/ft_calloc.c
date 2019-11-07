/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 22:07:15 by jjaniec           #+#    #+#             */
/*   Updated: 2019/11/07 20:20:38 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

static void		*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if (nmemb == 0 || size == 0)
	{
		nmemb = 1;
		size = 1;
	}
	if ((ptr = malloc(nmemb * size)))
		ft_bzero(ptr, nmemb * size);
	return (ptr);
}

void			*calloc(size_t nmemb, size_t size)
{
	void	*r;

	r = ft_calloc(nmemb, size);
	return (r);
}
