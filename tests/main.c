#include <malloc.h>
#include <tap.h>

int main()
{
	plan(1);
	// free(NULL);
	ok(1 != 0, "test");
	// ok(NULL != malloc(2), "NULL != malloc(2)");
	done_testing();
	return 0;
}
