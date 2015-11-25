#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "test.h"
#include "util.h"

int main(int argc, char **argv)
{
	size_t len = 0;
	intmax_t *array = NULL;
	struct timespec diff;
	if (argc < 2) {
		fprintf(stderr, "Usage: %s filename\n", *argv);
		return 1;
	}
	srand(time(NULL));
	load_numbers(argv[1], &array, &len);
	test_treesort(array, len, 1, &diff);
	printf("time:\t%ld.%.09ld\n", diff.tv_sec, diff.tv_nsec);
	free(array);

	return 0;
}
