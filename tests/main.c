/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 20:03:32 by jjaniec           #+#    #+#             */
/*   Updated: 2019/10/15 12:11:13 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>
#include <tap.h>

static int read_str_char(char *ptr, char c)
{
	int i;

	i = -1;
	while (ptr[++i])
		if (ptr[i] != c)
			return 1;
	return 0;
}

static void mem_saturation_test(size_t size, bool free)
{
	void *tmp;

	while ((tmp = ft_malloc(size)) != NULL)
	{
		;
	}
	ok(tmp == NULL, "Malloc return on mmap error test");
	if (free == true)
		ft_free_all();
}

static void ft_free_crash_tests(size_t size)
{
	char *tmp;
	char *tmp2;
	char *tmp3;

	tmp = ft_malloc(size);
	tmp2 = ft_malloc(size);
	tmp3 = ft_malloc(size);
	tmp[0] = '\0';
	tmp2[0] = '\0';
	tmp3[0] = '\0';
	ft_free(tmp2);
	tmp[0] = '\0';
	tmp3[0] = '\0';
	ft_free(tmp);
	tmp3[0] = '\0';
	ft_free(tmp3);
	ft_free(NULL);
}

static void basic_tests()
{
	char *tmp;

	tmp = ft_malloc(5);
	ok(NULL != tmp, "Malloc - Tiny 1 - Allocation");
	tmp[0] = 'a';
	tmp[1] = '\0';
	ok(tmp[0] == 'a', "Malloc - Tiny 1 - Assignation");
	ok(tmp[1] == '\0', "Malloc - Tiny 1 - Assignation 2");
	show_alloc_mem();
	ft_free(tmp);
	show_alloc_mem();
	// exit(1);

	tmp = ft_malloc(TINY_MAX_SIZE / 2 + 1);
	ok(NULL != tmp, "Malloc - Basic 1 - Basic tiny allocation");
	tmp[0] = 'A';
	ft_memset(tmp + 1, 'B', TINY_MAX_SIZE / 2 - 1);
	tmp[SMALL_MAX_SIZE / 2] = '\0';
	ok(tmp[0] == 'A', "Malloc - Basic 1 - Basic tiny assignation");
	ok(read_str_char(tmp + 1, 'B') == 0, "Malloc - Basic 2 - Basic tiny assignation 2");

	tmp = ft_malloc(SMALL_MAX_SIZE / 2 + 1);
	ok(NULL != tmp, "Malloc - Basic 3 - Basic small allocation");
	ft_memset(tmp, 'B', SMALL_MAX_SIZE / 2 - 1);
	tmp[SMALL_MAX_SIZE / 2] = '\0';
	ok(read_str_char(tmp, 'B') == 0, "Malloc - Basic 4 - Basic small assignation");

	tmp = ft_malloc(42000 + 1);
	ok(NULL != tmp, "Malloc - Basic 5 - Basic big allocation");
	ft_memset(tmp, 'B', 42000);
	tmp[42000] = '\0';
	ok(read_str_char(tmp, 'B') == 0, "Malloc - Basic 6 - Basic big assignation");

	show_alloc_mem();

	tmp = ft_malloc(SMALL_MAX_SIZE * 2 + 1);
	ok(NULL != tmp, "Malloc - Basic 7 - Basic big allocation 2");
	ft_memset(tmp, 'B', SMALL_MAX_SIZE * 2 - 1);
	tmp[SMALL_MAX_SIZE * 2] = '\0';
	ok(read_str_char(tmp, 'B') == 0, "Malloc - Basic 8 - Basic big assignation 2");

	ok(ft_malloc(0) != NULL, "Malloc - Basic 9 - Malloc(0)");
	ok(ft_malloc(293828371837313123) == NULL, "Malloc - Basic 10 - Malloc with too large number");
}

static void ft_free_tests()
{
	ft_free_crash_tests(TINY_MAX_SIZE / 2);
	ft_free_crash_tests(SMALL_MAX_SIZE / 2);
	ft_free_crash_tests(SMALL_MAX_SIZE * 4);
	ft_free_all();
}

static void calloc_tests()
{
	char *tmp;

	tmp = ft_calloc(6, sizeof(char));
	ok(NULL != tmp, "Calloc - Basic 1 - Basic allocation");
	ft_memset(tmp, 'B', 5);
	tmp[5] = '\0';
	ok(read_str_char(tmp, 'B') == 0, "Calloc - Basic 2 - Basic assignation");

	// ft_free_all();

	ok(NULL == ft_calloc(-1, sizeof(int)), "Calloc - error 1 - negative nmemb overflow");
	ok(NULL == ft_calloc(1, -1), "Calloc - error 2 - negative size overflow");
	ok(NULL == ft_calloc(2, -1), "Calloc - error 3 - negative size overflow");
	ok(NULL == ft_calloc(SIZE_MAX, sizeof(int)), "Calloc - error 4 - overflow");
	ok(NULL == ft_calloc(0, sizeof(int)), "Calloc - nmemb == 0");
	ok(NULL == ft_calloc(1, 0), "Calloc - size == 0");
}

static void realloc_tests()
{
	char *tmp;

	tmp = ft_calloc(6, sizeof(char));
	show_alloc_mem();
	ft_memset(tmp, 'B', 5);
	tmp[5] = '\0';
	tmp = ft_realloc(tmp, sizeof(char) * 3);
	tmp[2] = '\0';
	ok(tmp[0] == 'B', "Realloc - Basic 1 1");
	ok(tmp[1] == 'B', "Realloc - Basic 1 2");
	ok(tmp[2] == '\0', "Realloc - Basic 1 3");
	tmp = ft_realloc(tmp, sizeof(char) * 51);
	tmp[49] = '\0';
	tmp[30] = 'B';
	ok(tmp[0] == 'B', "Realloc - Basic 1 4");
	ok(tmp[30] == 'B', "Realloc - Basic 1 5");
	ok(tmp[2] == '\0', "Realloc - Basic 1 6");
	ok(tmp[49] == '\0', "Realloc - Basic 1 7");
	// ft_free(tmp);
}

int main()
{
	basic_tests();
	ft_free_all();
	show_alloc_mem();

	ft_free_tests();
	ft_free_all();

	calloc_tests();
	ft_free_all();

	show_alloc_mem();
	realloc_tests();
	ft_free_all();

	// mem_saturation_test(TINY_MAX_SIZE / 2, true);
	// mem_saturation_test(SMALL_MAX_SIZE / 2, true);
	// mem_saturation_test(SMALL_MAX_SIZE * 4096, true);

	show_alloc_mem();
	ft_free_all();

	done_testing();
	return 0;
}
