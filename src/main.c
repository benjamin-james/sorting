#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#include "util.h"
int insertion_sort(uint64_t *array, size_t size)
{
	size_t i, j;
	uint64_t temp;
	for (i = 1; i < size; i++) {
		temp = array[i];
		for (j = i; j > 0 && temp < array[j - 1]; j--) {
			array[j] = array[j-1];
		}
		array[j] = temp;
	}
	return 0;
}

int main(int argc, char *argv[])
{
	size_t len = 10;
	uint64_t *array = NULL;
	if (argc < 2) {
		fprintf(stderr, "Usage: %s filename\n", *argv);
		return 1;
	}
	load_numbers(argv[1], &array, &len);
	do_time(insertion_sort, array, len);
	free(array);
	return 0;
}
