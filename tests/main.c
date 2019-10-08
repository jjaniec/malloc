/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 20:03:32 by jjaniec           #+#    #+#             */
/*   Updated: 2019/10/08 16:22:20 by jjaniec          ###   ########.fr       */
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

static void		mem_saturation_test(size_t size, bool free) {
	void 	*tmp;

	while ((tmp = ft_malloc(size)) != NULL) 
	{
		;
	}
	ok(tmp == NULL, "Malloc return on mmap error test");
	if (free == true)
		ft_free_all();
}

static void		ft_free_crash_tests(size_t size) {
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

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

static void		tiny_tests(bool free) {
	char 	*tmp;
	// void	*tmp2;
	// void	*tmp3;

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

	// while (i++ < 100)
	// {
	// 	tmp = ft_malloc(SMALL_MAX_SIZE / 2 + 1);
	// 	ok(NULL != tmp, "Malloc - Small 2 - Basic allocation");
	// }

	if (free == true)
		ft_free_all();
	mem_saturation_test(TINY_MAX_SIZE / 2, free);
}

// static void		small_tests() {

// }

// static void		big_tests() {

// }

static void		basic_tests() {
	char	*tmp;

	tmp = ft_malloc(TINY_MAX_SIZE / 2 + 1);
	ok(NULL != tmp, "Malloc - Basic 1 - Basic tiny allocation");
	ft_memset(tmp, 'B', SMALL_MAX_SIZE / 2 - 1);
	tmp[SMALL_MAX_SIZE / 2] = '\0';
	ok(read_str_char(tmp, 'B') == 0, "Malloc - Basic 2 - Basic tiny assignation");

	tmp = ft_malloc(SMALL_MAX_SIZE / 2 + 1);
	ok(NULL != tmp, "Malloc - Basic 3 - Basic small allocation");
	ft_memset(tmp, 'B', SMALL_MAX_SIZE / 2 - 1);
	tmp[SMALL_MAX_SIZE / 2] = '\0';
	ok(read_str_char(tmp, 'B') == 0, "Malloc - Basic 4 - Basic small assignation");

	tmp = ft_malloc(SMALL_MAX_SIZE / 2 + 1);
	ok(NULL != tmp, "Malloc - Basic 5 - Basic big allocation");
	ft_memset(tmp, 'B', SMALL_MAX_SIZE / 2 - 1);
	tmp[SMALL_MAX_SIZE / 2] = '\0';
	ok(read_str_char(tmp, 'B') == 0, "Malloc - Basic 6 - Basic big assignation");

	ok(ft_malloc(0) != NULL, "Malloc - Basic 7 - Malloc(0)");
	ok(ft_malloc(293828371837313123) == NULL, "Malloc - Basic 8 - Malloc with too large number");
}

static void		ft_free_tests()
{
	ft_free_crash_tests(TINY_MAX_SIZE / 2);
	ft_free_crash_tests(SMALL_MAX_SIZE / 2);
	ft_free_crash_tests(SMALL_MAX_SIZE * 4);
	ft_free_all();
}

static void calloc_tests()
{
	char	*tmp;

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

int			main()
{
	basic_tests();
	ft_free_all();

	ft_free_tests();
	ft_free_all();

	calloc_tests();
	ft_free_all();

	mem_saturation_test(TINY_MAX_SIZE / 2, true);
	mem_saturation_test(SMALL_MAX_SIZE / 2, true);
	mem_saturation_test(SMALL_MAX_SIZE * 4096, true);

	ft_free_all();
	show_alloc_mem();

	done_testing();
	return 0;
}
