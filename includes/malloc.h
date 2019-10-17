/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 17:48:14 by jjaniec           #+#    #+#             */
/*   Updated: 2019/10/17 14:09:44 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include <libft.h>
# include <unistd.h>
# include <sys/mman.h>
# include <stdbool.h>
# include <stdlib.h>
# include <errno.h>
# include <stdint.h>

/*
** Allocations max size per allocation type
*/

// # define TINY_MAX_SIZE 256
// # define SMALL_MAX_SIZE 4096

// # define TINY_MAX_SIZE 64
// # define SMALL_MAX_SIZE 2048

# define TINY_MAX_SIZE 64
# define SMALL_MAX_SIZE 2048

/*
** Tiny & small pages size ( x * getpagesize() )
*/

// # define TINY_PAGE_SIZE 8
// # define SMALL_PAGE_SIZE 24

# define TINY_PAGE_SIZE 3
# define SMALL_PAGE_SIZE 100

// # define TINY_PAGE_SIZE 1
// # define SMALL_PAGE_SIZE 2

/*
** Initial number of pages in tiny & small page regions
*/

# define TINY_REGION_PAGE_COUNT 1
# define SMALL_REGION_PAGE_COUNT 1

/*
** mmap parameters for pages allocations
*/

# define PAGE_MMAP_PROT PROT_READ | PROT_WRITE
# define PAGE_MMAP_FLAGS MAP_ANON | MAP_PRIVATE

//
# define SHOW_ALLOC_MEM_BYTES_PER_LINE 16
# define SHOW_ALLOC_MEM_FREE_BLOCKS false
# define DISABLE_SHOW_ALLOC_DATA true

typedef struct				s_malloc_header
{
	bool					free : 1;
	char					_unused[3];
	size_t					size;
	struct s_malloc_header	*prev;
	struct s_malloc_header	*next;
}							t_malloc_header;

void			free(void *ptr);

void			*malloc(size_t size);

void			*calloc(size_t nmemb, size_t size);

void			*realloc(void *ptr, size_t size);

void			show_alloc_mem(void);

t_malloc_header	*get_alloc_header(void *ptr, int *alloc_mem_index);

void			free_alloc(t_malloc_header *alloc_header, int alloc_mem_index);

void			ft_free_all(void);

int				get_alloc_type(size_t size);

void			write_header(void *ptr, bool free, size_t size, \
					t_malloc_header *prev, t_malloc_header *next);

void			ft_putnbr_base(int n, unsigned int base);

#endif
