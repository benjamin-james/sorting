#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#include "util.h"
#include "sorting.h"

int test_merge_sort(const uint64_t *orig_array, size_t size, struct timeval *real_diff, struct timeval *user_diff, struct timeval *sys_diff)
{
	uint64_t *array = NULL, *cpy_array = NULL;
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
#ifdef DEBUG
	print_array(stdout, array, size);
#endif
	if (array) {
		free(array);
	}
	if (cpy_array) {
		free(cpy_array);
	}
	return 0;
}
int test_insertion_sort(const uint64_t *orig_array, size_t size, struct timeval *real_diff, struct timeval *user_diff, struct timeval *sys_diff)
{
	uint64_t *array = NULL;
	struct timeval start_tv, end_tv;
	struct rusage start_ru, end_ru;
	dup_array(orig_array, size, &array);
	get_clock(&start_tv, &start_ru);
	insertion_sort(array, size);
	get_clock(&end_tv, &end_ru);
	timeval_diff(start_tv, end_tv, real_diff);
	timeval_diff(start_ru.ru_utime, end_ru.ru_utime, user_diff);
	timeval_diff(start_ru.ru_stime, end_ru.ru_stime, sys_diff);
#ifdef DEBUG
	print_array(stdout, array, size);
#endif
	if (array) {
		free(array);
	}
	return 0;
}
int test_bubble_sort(const uint64_t *orig_array, size_t size, struct timeval *real_diff, struct timeval *user_diff, struct timeval *sys_diff)
{
	uint64_t *array = NULL;
	struct timeval start_tv, end_tv;
	struct rusage start_ru, end_ru;
	dup_array(orig_array, size, &array);
	get_clock(&start_tv, &start_ru);
	bubble_sort(array, size);
	get_clock(&end_tv, &end_ru);
	timeval_diff(start_tv, end_tv, real_diff);
	timeval_diff(start_ru.ru_utime, end_ru.ru_utime, user_diff);
	timeval_diff(start_ru.ru_stime, end_ru.ru_stime, sys_diff);
#ifdef DEBUG
	print_array(stdout, array, size);
#endif
	if (array) {
		free(array);
	}
	return 0;
}
int test_hybrid_sort(const uint64_t *orig_array, size_t size, int cutoff, struct timeval *real_diff, struct timeval *user_diff, struct timeval *sys_diff)
{
	uint64_t *array = NULL, *cpy_array = NULL;
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
#ifdef DEBUG
	print_array(stdout, array, size);
#endif
	if (array) {
		free(array);
	}
	if (cpy_array) {
		free(cpy_array);
	}
	return 0;
}
int main(int argc, char **argv)
{
	size_t len = 10;
	uint64_t *array = NULL;
	struct timeval real_diff, user_diff, sys_diff;
	if (argc < 2) {
		fprintf(stderr, "Usage: %s filename\n", *argv);
		return 1;
	}
	load_numbers(argv[1], &array, &len);
	test_hybrid_sort(array, len, 7, &real_diff, &user_diff, &sys_diff);
	printf("real:\t%ld.%.06ld\n", real_diff.tv_sec, real_diff.tv_usec);
	printf("user:\t%ld.%.06ld\n", user_diff.tv_sec, user_diff.tv_usec);
	printf("sys:\t%ld.%.06ld\n", sys_diff.tv_sec, sys_diff.tv_usec);
	free(array);

	return 0;
}
