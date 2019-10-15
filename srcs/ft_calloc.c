/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 22:07:15 by jjaniec           #+#    #+#             */
/*   Updated: 2019/10/15 12:12:13 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

void *calloc(size_t nmemb, size_t size)
{
	void *ptr;

	ft_putstr("Calloc ");
	ft_putnbr((unsigned long)nmemb * size);
	ft_putchar('\n');

	if (nmemb == 0 || size == 0 || SIZE_MAX / nmemb <= size)
		return NULL;
	if ((ptr = malloc(nmemb * size)))
		ft_bzero(ptr, nmemb * size);
	return ptr;
}
