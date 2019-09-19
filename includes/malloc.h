/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 17:48:14 by jjaniec           #+#    #+#             */
/*   Updated: 2019/09/19 13:47:07 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include <libft.h>
# include <unistd.h>
# include <sys/mman.h>
# include <stdbool.h>
# include <stdlib.h>

// Allocations max size per allocation type
# define TINY_MAX_SIZE 256
# define SMALL_MAX_SIZE 4096

// Tiny & small pages size ( x * getpagesize() )
# define TINY_PAGE_SIZE 8
# define SMALL_PAGE_SIZE 24

// Initial number of pages in tiny & small page regions
# define TINY_REGION_PAGE_COUNT 1
# define SMALL_REGION_PAGE_COUNT 1

// mmap parameters for pages allocations
# define PAGE_MMAP_PROT PROT_READ | PROT_WRITE | PROT_EXEC
# define PAGE_MMAP_FLAGS MAP_ANON | MAP_PRIVATE

//
# define SHOW_ALLOC_MEM_BYTES_PER_LINE	16
# define SHOW_ALLOC_MEM_FREE_BLOCKS false

typedef						struct s_malloc_header
{
	bool					free : 1;
	char					_unused[3];
	unsigned int			size;
	struct s_malloc_header	*prev;
	struct s_malloc_header	*next;
}							t_malloc_header;

void						ft_free(void *ptr);
void						*ft_malloc(size_t size);
void						*ft_realloc(void *ptr, size_t size);
void						show_alloc_mem(void);
void						ft_free_all(void);

#endif
