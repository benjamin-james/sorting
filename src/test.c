#include <stdlib.h>

#include "sorting.h"
#include "test.h"
#include "util.h"

int test_treesort(const intmax_t *orig_array, size_t size, bool print, struct timeval *real_diff, struct timeval *user_diff, struct timeval *sys_diff) {
	struct tree *t;
	struct timeval start_tv, end_tv;
	struct rusage start_ru, end_ru;
	get_clock(&start_tv, &start_ru);
	treesort(orig_array, size, &t);
	get_clock(&end_tv, &end_ru);
       	timeval_diff(start_tv, end_tv, real_diff);
	timeval_diff(start_ru.ru_utime, end_ru.ru_utime, user_diff);
	timeval_diff(start_ru.ru_stime, end_ru.ru_stime, sys_diff);
	if (print) {
		print_tree(stdout, t);
	}
       	tree_free(t);
	return 0;
}

int test_heapsort(const intmax_t *orig_array, size_t size, bool print, struct timeval *real_diff, struct timeval *user_diff, struct timeval *sys_diff) {
	intmax_t *array = NULL;
	struct timeval start_tv, end_tv;
	struct rusage start_ru, end_ru;
	dup_array(orig_array, size, &array);
	get_clock(&start_tv, &start_ru);
	heapsort(array, size);
	get_clock(&end_tv, &end_ru);
       	timeval_diff(start_tv, end_tv, real_diff);
	timeval_diff(start_ru.ru_utime, end_ru.ru_utime, user_diff);
	timeval_diff(start_ru.ru_stime, end_ru.ru_stime, sys_diff);
	if (print) {
		print_array(stdout, array, size);
	}
	if (array) {
		free(array);
	}
	return 0;
}

int test_quicksort(const intmax_t *orig_array, size_t size, bool print, struct timeval *real_diff, struct timeval *user_diff, struct timeval *sys_diff) {
	intmax_t *array = NULL;
	struct timeval start_tv, end_tv;
	struct rusage start_ru, end_ru;
	dup_array(orig_array, size, &array);
	get_clock(&start_tv, &start_ru);
	quicksort(array, 0, size-1, &first_pivot);
	get_clock(&end_tv, &end_ru);
       	timeval_diff(start_tv, end_tv, real_diff);
	timeval_diff(start_ru.ru_utime, end_ru.ru_utime, user_diff);
	timeval_diff(start_ru.ru_stime, end_ru.ru_stime, sys_diff);
	if (print) {
		print_array(stdout, array, size);
	}
	if (array) {
		free(array);
	}
	return 0;
}

int test_mergesort(const intmax_t *orig_array, size_t size, bool print, struct timeval *real_diff, struct timeval *user_diff, struct timeval *sys_diff)
{
	intmax_t *array = NULL, *cpy_array = NULL;
	struct timeval start_tv, end_tv;
	struct rusage start_ru, end_ru;
	dup_array(orig_array, size, &array);
	dup_array(orig_array, size, &cpy_array);
	get_clock(&start_tv, &start_ru);
	merge_sort(array, 0, size, cpy_array);
	get_clock(&end_tv, &end_ru);
	timeval_diff(start_tv, end_tv, real_diff);
	timeval_diff(start_ru.ru_utime, end_ru.ru_utime, user_diff);
	timeval_diff(start_ru.ru_stime, end_ru.ru_stime, sys_diff);
	if (print) {
		print_array(stdout, array, size);
	}
	if (array) {
		free(array);
	}
	if (cpy_array) {
		free(cpy_array);
	}
	return 0;
}
int test_insertion_sort(const intmax_t *orig_array, size_t size, bool print, struct timeval *real_diff, struct timeval *user_diff, struct timeval *sys_diff)
{
	intmax_t *array = NULL;
	struct timeval start_tv, end_tv;
	struct rusage start_ru, end_ru;
	dup_array(orig_array, size, &array);
	get_clock(&start_tv, &start_ru);
	insertion_sort(array, size);
	get_clock(&end_tv, &end_ru);
	timeval_diff(start_tv, end_tv, real_diff);
	timeval_diff(start_ru.ru_utime, end_ru.ru_utime, user_diff);
	timeval_diff(start_ru.ru_stime, end_ru.ru_stime, sys_diff);
	if (print) {
		print_array(stdout, array, size);
	}
	if (array) {
		free(array);
	}
	return 0;
}
int test_bubble_sort(const intmax_t *orig_array, size_t size, bool print, struct timeval *real_diff, struct timeval *user_diff, struct timeval *sys_diff)
{
	intmax_t *array = NULL;
	struct timeval start_tv, end_tv;
	struct rusage start_ru, end_ru;
	dup_array(orig_array, size, &array);
	get_clock(&start_tv, &start_ru);
	bubble_sort(array, size);
	get_clock(&end_tv, &end_ru);
	timeval_diff(start_tv, end_tv, real_diff);
	timeval_diff(start_ru.ru_utime, end_ru.ru_utime, user_diff);
	timeval_diff(start_ru.ru_stime, end_ru.ru_stime, sys_diff);
	if (print) {
		print_array(stdout, array, size);
	}
	if (array) {
		free(array);
	}
	return 0;
}
int test_hybrid_sort(const intmax_t *orig_array, size_t size, int cutoff, bool print, struct timeval *real_diff, struct timeval *user_diff, struct timeval *sys_diff)
{
	intmax_t *array = NULL, *cpy_array = NULL;
	struct timeval start_tv, end_tv;
	struct rusage start_ru, end_ru;
	dup_array(orig_array, size, &array);
	dup_array(orig_array, size, &cpy_array);
	get_clock(&start_tv, &start_ru);
	hybrid_sort(array, 0, size, cpy_array, cutoff);
	get_clock(&end_tv, &end_ru);
	timeval_diff(start_tv, end_tv, real_diff);
	timeval_diff(start_ru.ru_utime, end_ru.ru_utime, user_diff);
	timeval_diff(start_ru.ru_stime, end_ru.ru_stime, sys_diff);
	if (print) {
		print_array(stdout, array, size);
	}
	if (array) {
		free(array);
	}
	if (cpy_array) {
		free(cpy_array);
	}
	return 0;
}
