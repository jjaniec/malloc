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

	tmp = ft_malloc(2);
	ok(NULL != tmp, "Malloc - Tiny 1 - Allocation");
	tmp[0] = 'a';
	tmp[1] = '\0';
	ok(tmp[0] == 'a', "Malloc - Tiny 1 - Assignation");
	ok(tmp[1] == '\0', "Malloc - Tiny 1 - Assignation 2");

	tmp = ft_malloc(TINY_MAX_SIZE / 2 + 1);
	ok(NULL != tmp, "Malloc - Tiny 2 - Allocation");
	ft_memset(tmp, 'b', TINY_MAX_SIZE / 2 - 1);
	tmp[TINY_MAX_SIZE / 2] = '\0';
	ok(read_str_char(tmp, 'b') == 0, "Malloc - Tiny 2 - String Assignation");

	tmp = ft_malloc(TINY_MAX_SIZE / 2 + 1);
	ok(NULL != tmp, "Malloc - Tiny 3 - Allocation on different page");
	ft_memset(tmp, 'A', TINY_MAX_SIZE / 2 - 1);
	tmp[TINY_MAX_SIZE / 2] = '\0';
	ok(read_str_char(tmp, 'A') == 0, "Malloc - Tiny 3 - String Assignation on different page");

	tmp = ft_malloc(SMALL_MAX_SIZE / 2 + 1);
	ok(NULL != tmp, "Malloc - Small 1 - Basic allocation");
	ft_memset(tmp, 'B', SMALL_MAX_SIZE / 2 - 1);
	tmp[SMALL_MAX_SIZE / 2] = '\0';
	ok(read_str_char(tmp, 'B') == 0, "Malloc - Small 1 - String assignation");

	tmp = ft_malloc(SMALL_MAX_SIZE * 2 + 1);
	ok(NULL != tmp, "Malloc - Big 1 - Basic allocation");
	ft_memset(tmp, 'C', SMALL_MAX_SIZE * 2 - 1);
	tmp[SMALL_MAX_SIZE * 2] = '\0';
	ok(read_str_char(tmp, 'C') == 0, "Malloc - Big 1 - String assignation");

	show_alloc_mem();

	done_testing();
	return 0;
}
