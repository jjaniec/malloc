#include <malloc.h>
#include <tap.h>

int main()
{
	// plan(1);
	// free(NULL);
	// ok(1 != 0, "test");
	ok(NULL != ft_malloc(2), "NULL != malloc(2)");
	ok(NULL != ft_malloc(256), "NULL != malloc(256)");
	char * tmp;
	tmp = ft_malloc(25);
	tmp[0] = 'a';
	ok(tmp[0] == 'a', "Test write");
	done_testing();
	return 0;
}
