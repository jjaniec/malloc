/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 17:48:14 by jjaniec           #+#    #+#             */
/*   Updated: 2019/09/16 16:06:00 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
#define MALLOC_H

#include <libft.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdbool.h>
#include <stdlib.h>

// Allocations region size (multiplier of get_page_size())
#define TINY_PAGE_SIZE_COUNT 1
#define SMALL_PAGE_SIZE_COUNT 4

// Allocations max size per allocation type
#define TINY_MAX_SIZE 124
#define SMALL_MAX_SIZE 126000

// mmap parameters for pages allocations
#define PAGE_MMAP_PROT PROT_READ | PROT_WRITE | PROT_EXEC
#define PAGE_MMAP_FLAGS MAP_ANON | MAP_PRIVATE

// Initial number of pages in tiny & small page regions
#define TINY_REGION_PAGE_COUNT 5
#define SMALL_REGION_PAGE_COUNT 5

typedef struct s_malloc_header
{
	bool freed;
	unsigned int size;
	struct s_malloc_header *prev;
	struct s_malloc_header *next;
} t_malloc_header;

void ft_free(void *ptr);
void *ft_malloc(size_t size);
void *ft_realloc(void *ptr, size_t size);
void show_alloc_mem(void);

#endif
