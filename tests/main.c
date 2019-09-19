/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 20:03:32 by jjaniec           #+#    #+#             */
/*   Updated: 2019/09/19 23:57:48 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>
#include <tap.h>

static int	read_str_char(char *ptr, char c)
{
	int	i;

	i = -1;
	while (ptr[++i])
		if (ptr[i] != c)
			return 1;
	return 0;
}

int			main()
{
	char	*tmp;
	char	*tmp2;
	int		i;

	tmp = ft_malloc(5);
	ok(NULL != tmp, "Malloc - Tiny 1 - Allocation");
	tmp[0] = 'a';
	tmp[1] = '\0';
	ok(tmp[0] == 'a', "Malloc - Tiny 1 - Assignation");
	ok(tmp[1] == '\0', "Malloc - Tiny 1 - Assignation 2");
	ft_free(tmp);

	tmp = ft_malloc(TINY_MAX_SIZE / 2 + 1);
	ok(NULL != tmp, "Malloc - Tiny 2 - Allocation");
	ft_memset(tmp, 'b', TINY_MAX_SIZE / 2 - 1);
	tmp[TINY_MAX_SIZE / 2] = '\0';
	ok(read_str_char(tmp, 'b') == 0, "Malloc - Tiny 2 - String Assignation");

	tmp = ft_malloc(TINY_MAX_SIZE / 2 + 1);
	ok(NULL != tmp, "Malloc - Tiny 3 - Allocation 2");
	ft_memset(tmp, 'A', TINY_MAX_SIZE / 2 - 1);
	tmp[TINY_MAX_SIZE / 2] = '\0';
	ok(read_str_char(tmp, 'A') == 0, "Malloc - Tiny 3 - String Assignation 2");
	ft_free(tmp);

	i = 0;
	while (i < getpagesize() * TINY_PAGE_SIZE)
	{
		ok(NULL != ft_malloc(TINY_MAX_SIZE), "Fill tiny page allocation with TINY_MAX_SIZE");
		i += TINY_MAX_SIZE;
	}

	tmp = ft_malloc(SMALL_MAX_SIZE / 2 + 1);
	ok(NULL != tmp, "Malloc - Small 1 - Basic allocation");
	ft_memset(tmp, 'B', SMALL_MAX_SIZE / 2 - 1);
	tmp[SMALL_MAX_SIZE / 2] = '\0';
	ok(read_str_char(tmp, 'B') == 0, "Malloc - Small 1 - String assignation");

	i = 0;
	while (i++ < 100)
	{
		tmp = ft_malloc(SMALL_MAX_SIZE / 2 + 1);
		ok(NULL != tmp, "Malloc - Small 2 - Basic allocation");
	}

	tmp = ft_malloc(SMALL_MAX_SIZE * 2 + 1);
	ok(NULL != tmp, "Malloc - Big 1 - Basic allocation");
	ft_memset(tmp, 'C', SMALL_MAX_SIZE * 2 - 1);
	tmp[SMALL_MAX_SIZE * 2] = '\0';
	ok(read_str_char(tmp, 'C') == 0, "Malloc - Big 1 - String assignation");

	i = 0;
	while (i++ < 100)
	{
		tmp = ft_malloc(SMALL_MAX_SIZE * 2 + 1);
		ok(NULL != tmp, "Malloc - Big 2 - Basic allocation");
	}

	show_alloc_mem();
	ft_free_all();
	show_alloc_mem();

	done_testing();
	return 0;
}
