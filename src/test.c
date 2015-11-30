#include <stdlib.h>

#include "sorting.h"
#include "test.h"
#include "util.h"

int test_treesort(const intmax_t *orig_array, size_t size, bool print, struct timespec *diff) {
	struct tree *t;
	struct timespec start, end;
	get_clock(&start);
	treesort(orig_array, size, &t);
	get_clock(&end);
       	timespec_diff(start, end, diff);
	if (print) {
		print_tree(stdout, t);
	}
       	tree_free(t);
	return 0;
}

int test_heapsort(const intmax_t *orig_array, size_t size, bool print, struct timespec *diff)
{
	intmax_t *array = NULL;
	struct timespec start, end;
	dup_array(orig_array, size, &array);
	get_clock(&start);
	heapsort(array, size);
	get_clock(&end);
       	timespec_diff(start, end, diff);
	if (print) {
		print_array(stdout, array, size);
	}
	if (array) {
		free(array);
	}
	return 0;
}

int test_quicksort(const intmax_t *orig_array, size_t size, int (*choose_pivot)(const intmax_t *array, size_t begin, size_t end), bool print, struct timespec *diff)
{
	intmax_t *array = NULL;
	struct timespec start, end;
	dup_array(orig_array, size, &array);
	get_clock(&start);
	quicksort(array, 0, size-1, choose_pivot);
	get_clock(&end);
       	timespec_diff(start, end, diff);
	if (print) {
		print_array(stdout, array, size);
	}
	if (array) {
		free(array);
	}
	return 0;
}
int test_mergesort(const intmax_t *orig_array, size_t size, bool print, struct timespec *diff)
{
	intmax_t *array = NULL, *cpy_array = NULL;
	struct timespec start, end;
	dup_array(orig_array, size, &array);
	get_clock(&start);
	dup_array(orig_array, size, &cpy_array);
	merge_sort(array, 0, size, cpy_array);
	if (cpy_array) {
		free(cpy_array);
	}
	get_clock(&end);
	timespec_diff(start, end, diff);
	if (print) {
		print_array(stdout, array, size);
	}
	if (array) {
		free(array);
	}
	return 0;
}
int test_insertion_sort(const intmax_t *orig_array, size_t size, bool print, struct timespec *diff)
{
	intmax_t *array = NULL;
	struct timespec start, end;
	dup_array(orig_array, size, &array);
	get_clock(&start);
	insertion_sort(array, size);
	get_clock(&end);
	timespec_diff(start, end, diff);
	if (print) {
		print_array(stdout, array, size);
	}
	if (array) {
		free(array);
	}
	return 0;
}
int test_bubble_sort(const intmax_t *orig_array, size_t size, bool print, struct timespec *diff)
{
	intmax_t *array = NULL;
	struct timespec start, end;
	dup_array(orig_array, size, &array);
	get_clock(&start);
	bubble_sort(array, size);
	get_clock(&end);
	timespec_diff(start, end, diff);
	if (print) {
		print_array(stdout, array, size);
	}
	if (array) {
		free(array);
	}
	return 0;
}
int test_hybrid_sort(const intmax_t *orig_array, size_t size, int cutoff, bool print, struct timespec *diff)
{
	intmax_t *array = NULL, *cpy_array = NULL;
	struct timespec start, end;
	dup_array(orig_array, size, &array);
	get_clock(&start);
	dup_array(orig_array, size, &cpy_array);
	hybrid_sort(array, 0, size, cpy_array, cutoff);
	if (cpy_array) {
		free(cpy_array);
	}
	get_clock(&end);
	timespec_diff(start, end, diff);
	if (print) {
		print_array(stdout, array, size);
	}
	if (array) {
		free(array);
	}
	return 0;
}
