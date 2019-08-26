/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 17:48:14 by eparisot          #+#    #+#             */
/*   Updated: 2019/08/26 20:36:25 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
#define MALLOC_H

#include <libft.h>
#include <unistd.h>
#include <sys/mman.h>

void ft_free(void *ptr);
void *ft_malloc(size_t size);
void *ft_realloc(void *ptr, size_t size);
void show_alloc_mem(void);

#endif
