/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 11:36:57 by eparisot          #+#    #+#             */
/*   Updated: 2019/08/26 20:36:13 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

void ft_free(void *ptr)
{
	printf("requested free at : %p\n", ptr);

	//if(munmap(ptr, 0) != 0)
	//	ft_putstr("free Error");
}
