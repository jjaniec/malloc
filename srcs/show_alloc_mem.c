/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 15:14:11 by jjaniec           #+#    #+#             */
/*   Updated: 2019/09/19 22:38:15 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

extern t_malloc_header	*g_alloc_mem[3];

static void	print_alloc_data(t_malloc_header *header)
{
	unsigned int	i;
	unsigned int	j;
	char			cur_byte_value;
	unsigned int	line_start_offset;
	char			*byte_hex_fmt;

	i = 0;
	while (i < header->size)
	{
		printf("%p+%u:\t", header + sizeof(t_malloc_header), i);
		fflush(stdout);
		j = SHOW_ALLOC_MEM_BYTES_PER_LINE;
		line_start_offset = i;
		while (j-- && i < header->size)
		{
			cur_byte_value = ((char *)(header + sizeof(t_malloc_header)))[i];
			if (cur_byte_value < 10)
				ft_putchar('0');
			byte_hex_fmt = ft_itoa_base(cur_byte_value, 16);
			ft_putstr(byte_hex_fmt);
			free(byte_hex_fmt);
			if (i % 2)
				ft_putchar(' ');
			i += 1;
		}
		ft_putchar('\t');
		while (line_start_offset++ != i)
		{
			cur_byte_value = ((char *)(header + sizeof(t_malloc_header)))[line_start_offset];
			ft_putchar((ft_isprint(cur_byte_value)) ? cur_byte_value : '.');
		}
		ft_putchar('\n');
	}
}

static void	show_alloc_mem_list(char *type, t_malloc_header *start)
{
	while (start)
	{
		printf("%s block of size %zu @%p, free: %d\n", type, start->size, start, start->free);
		if (!DISABLE_SHOW_ALLOC_DATA && (SHOW_ALLOC_MEM_FREE_BLOCKS || !start->free))
		{
			print_alloc_data(start);
			fflush(stdout);
		}
		start = start->next;
	}
}

void		show_alloc_mem(void)
{
	printf("===== show_alloc_mem =====\n");
	show_alloc_mem_list("Tiny", g_alloc_mem[0]);
	show_alloc_mem_list("Small", g_alloc_mem[1]);
	show_alloc_mem_list("Big", g_alloc_mem[2]);
	printf("==========================\n");
}
