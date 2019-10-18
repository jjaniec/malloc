/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 22:07:15 by jjaniec           #+#    #+#             */
/*   Updated: 2019/10/18 19:31:27 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

void	*calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if (nmemb == 0 || size == 0 /*|| SIZE_MAX / nmemb <= size*/)
	{
		nmemb = 1;
		size = 1;
	}
	if ((ptr = malloc(nmemb * size)))
		ft_bzero(ptr, nmemb * size);
	return (ptr);
}
