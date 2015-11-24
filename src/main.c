#include <stdio.h>
#include <stdlib.h>

#include "test.h"
#include "util.h"

int main(int argc, char **argv)
{
	size_t len = 10;
	intmax_t *array = NULL;
	struct timeval real_diff, user_diff, sys_diff;
	if (argc < 2) {
		fprintf(stderr, "Usage: %s filename\n", *argv);
		return 1;
	}
	load_numbers(argv[1], &array, &len);
	test_treesort(array, len, 1, &real_diff, &user_diff, &sys_diff);
	printf("real:\t%ld.%.06ld\n", real_diff.tv_sec, real_diff.tv_usec);
	printf("user:\t%ld.%.06ld\n", user_diff.tv_sec, user_diff.tv_usec);
	printf("sys:\t%ld.%.06ld\n", sys_diff.tv_sec, sys_diff.tv_usec);
	free(array);

	return 0;
}
