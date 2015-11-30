#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "input.h"
#include "sorting.h"
#include "test.h"
#include "util.h"

int do_sort(intmax_t *array, size_t len, int sort, intptr_t cutoff, bool reg_pivot, bool print, struct timespec *diff);

int main(int argc, char **argv)
{
	intmax_t *array = NULL;
	size_t len = 0;
	int sorting = 0;
	char default_input[] = "/dev/stdin";
	char *input = default_input;
	intptr_t cutoff = 1;
	bool print = 1, do_time = 0, reg_pivot = 1;
	struct timespec diff;
	int ret = do_getopt(argc, argv, &sorting, &input, &reg_pivot, &cutoff, &print, &do_time);
	if (ret < 0) {
		goto end;
	}
	ret = load_numbers(input, &array, &len);
	if (ret < 0) {
		goto end;
	}
	ret = do_sort(array, len, sorting, cutoff, reg_pivot, print, &diff);
	if (ret < 0) {
		goto end;
	}
	if (do_time) {
		printf("time:\t%ld.%.09ld\n", diff.tv_sec, diff.tv_nsec);
	}
end:
	if (array) {
		free(array);
	}
	return ret;
}

int do_sort(intmax_t *array, size_t len, int sort, intptr_t cutoff, bool reg_pivot, bool print, struct timespec *diff)
{
	int ret = 0;
	switch (sort) {
	case TREE_SORT: {
		ret = test_treesort(array, len, print, diff);
		break;
	}
	case HEAP_SORT: {
		ret = test_heapsort(array, len, print, diff);
		break;
	}
	case QUICK_SORT: {
		if (reg_pivot) {
			ret = test_quicksort(array, len, &first_pivot, print, diff);
		} else {
			srand(time(NULL));
			ret = test_quicksort(array, len, &random_pivot, print, diff);
		}
		break;
	}
	case MERGE_SORT: {
		ret = test_mergesort(array, len, print, diff);
		break;
	}
	case INSERTION_SORT: {
		ret = test_insertion_sort(array, len, print, diff);
		break;
	}
	case BUBBLE_SORT: {
		ret = test_bubble_sort(array, len, print, diff);
		break;
	}
	case HYBRID_SORT: {
		ret = test_hybrid_sort(array, len, cutoff, print, diff);
		break;
	}
	default:
		ret = -1;
		break;
	}
	return ret;
}
