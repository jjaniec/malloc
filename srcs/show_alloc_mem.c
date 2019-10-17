/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 15:14:11 by jjaniec           #+#    #+#             */
/*   Updated: 2019/10/17 14:31:00 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

extern t_malloc_header *g_alloc_mem[3];

static void		print_byte_value(char byte)
{
	if (byte < 10)
		ft_putchar('0');
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
		ft_putstr("0x");
		ft_putnbr_base((unsigned int)header, 16);
		ft_putstr("+");
		ft_putnbr_base((unsigned int)i, 10);
		ft_putstr(":\t");
		j = SHOW_ALLOC_MEM_BYTES_PER_LINE;
		line_start_offset = i;
		while (j-- && i < header->size)
		{
			print_byte_value(((char *)((void *)header + sizeof(t_malloc_header)))[i]);
			if (i++ % 2)
				ft_putchar(' ');
		}
		ft_putchar('\t');
		while (line_start_offset != i)
		{
			cur_byte_value = ((char *)((void *)header + sizeof(t_malloc_header)))[line_start_offset];
			ft_putchar((ft_isprint(cur_byte_value)) ? cur_byte_value : '.');
			line_start_offset += 1;
		}
		ft_putchar('\n');
	}
}

static void		print_block_info(char *type, t_malloc_header *block)
{
	ft_putstr(type);
	ft_putstr(" block of size: ");
	ft_putnbr_base((unsigned int)block->size, 10);
	ft_putstr(" @0x");
	ft_putnbr_base((unsigned int)block, 16);
	ft_putstr(" - free: ");
	ft_putstr((block->free) ? ("true") : ("false"));
	ft_putstr(" prev: 0x");
	ft_putnbr_base((unsigned int)block->prev, 16);
	ft_putstr(" - next: 0x");
	ft_putnbr_base((unsigned int)block->next, 16);
	ft_putstr("\n");
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
	ft_putstr("===== show_alloc_mem =====\n");
	show_alloc_mem_list("Tiny", g_alloc_mem[0]);
	show_alloc_mem_list("Small", g_alloc_mem[1]);
	show_alloc_mem_list("Big", g_alloc_mem[2]);
	ft_putstr("==========================\n");
}
