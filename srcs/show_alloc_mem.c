/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 15:14:11 by jjaniec           #+#    #+#             */
/*   Updated: 2019/10/17 16:57:28 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

extern t_malloc_header *g_alloc_mem[3];

static void		print_byte_value(char byte)
{
	if (byte < 10)
		ft_putchar_fd('0', MALLOC_DEBUG_FD);
	ft_putnbr_base(byte, 16);
}

static void		print_alloc_data(t_malloc_header *header)
{
	unsigned int	i;
	unsigned int	j;
	char			cur_byte_value;
	unsigned int	line_start_offset;

	i = 0;
	while (i < header->size)
	{
		ft_putstr_fd("0x", MALLOC_DEBUG_FD);
		ft_putnbr_base((unsigned int)header, 16);
		ft_putstr_fd("+", MALLOC_DEBUG_FD);
		ft_putnbr_base((unsigned int)i, 10);
		ft_putstr_fd(":\t", MALLOC_DEBUG_FD);
		j = SHOW_ALLOC_MEM_BYTES_PER_LINE;
		line_start_offset = i;
		while (j-- && i < header->size)
		{
			print_byte_value(((char *)((void *)header + sizeof(t_malloc_header)))[i]);
			if (i++ % 2)
				ft_putchar_fd(' ', MALLOC_DEBUG_FD);
		}
		ft_putchar_fd('\t', MALLOC_DEBUG_FD);
		while (line_start_offset != i)
		{
			cur_byte_value = ((char *)((void *)header + sizeof(t_malloc_header)))[line_start_offset];
			ft_putchar_fd((ft_isprint(cur_byte_value)) ? cur_byte_value : '.', MALLOC_DEBUG_FD);
			line_start_offset += 1;
		}
		ft_putchar_fd('\n', MALLOC_DEBUG_FD);
	}
}

static void		print_block_info(char *type, t_malloc_header *block)
{
	ft_putstr_fd(type, MALLOC_DEBUG_FD);
	ft_putstr_fd(" block of size: ", MALLOC_DEBUG_FD);
	ft_putnbr_base((unsigned int)block->size, 10);
	ft_putstr_fd(" @0x", MALLOC_DEBUG_FD);
	ft_putnbr_base((unsigned int)block, 16);
	ft_putstr_fd(" - free: ", MALLOC_DEBUG_FD);
	ft_putstr_fd((block->free) ? ("true") : ("false"), MALLOC_DEBUG_FD);
	ft_putstr_fd(" prev: 0x", MALLOC_DEBUG_FD);
	ft_putnbr_base((unsigned int)block->prev, 16);
	ft_putstr_fd(" - next: 0x", MALLOC_DEBUG_FD);
	ft_putnbr_base((unsigned int)block->next, 16);
	ft_putstr_fd("\n", MALLOC_DEBUG_FD);
}

static void		show_alloc_mem_list(char *type, t_malloc_header *start)
{
	while (start)
	{
		print_block_info(type, start);
		if (!DISABLE_SHOW_ALLOC_DATA && \
			(SHOW_ALLOC_MEM_FREE_BLOCKS || !start->free))
		{
			print_alloc_data(start);
		}
		start = start->next;
	}
}

void			show_alloc_mem(void)
{
	fflush(stdout);
	ft_putstr_fd("===== show_alloc_mem =====\n", MALLOC_DEBUG_FD);
	ft_putstr_fd("pagesize: ", MALLOC_DEBUG_FD);
	ft_putnbr_fd((long unsigned int)getpagesize(), MALLOC_DEBUG_FD);
	ft_putstr_fd(" - Max tiny size: ", MALLOC_DEBUG_FD);
	ft_putnbr_fd((long unsigned int)getpagesize() * TINY_PAGE_SIZE, MALLOC_DEBUG_FD);
	ft_putstr_fd(" - Max small size: \n", MALLOC_DEBUG_FD);
	ft_putnbr_fd((long unsigned int)getpagesize() * SMALL_PAGE_SIZE, MALLOC_DEBUG_FD);
	ft_putstr_fd("==========================\n", MALLOC_DEBUG_FD);
	show_alloc_mem_list("Tiny", g_alloc_mem[0]);
	show_alloc_mem_list("Small", g_alloc_mem[1]);
	show_alloc_mem_list("Big", g_alloc_mem[2]);
	ft_putstr_fd("==========================\n", MALLOC_DEBUG_FD);
}
