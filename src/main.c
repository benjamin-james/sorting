#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
int merge_sort(uint64_t *array, size_t begin, size_t end, uint64_t *other_array)
{
	if (end - begin < 2) {
		return 0;
	}
	size_t middle = (end + begin) / 2;
	merge_sort(array, begin, middle, other_array);
	merge_sort(array, middle, end, other_array);
	size_t i, left = begin, right = middle;
	for (i = begin; i < end; i++) {
		if (left < middle && (right >= end || array[left] <= array[right])) {
			other_array[i] = array[left++];
		} else {
			other_array[i] = array[right++];
		}
	}
	memcpy(array + begin, other_array + begin, (end - begin) * sizeof *array);
	return 0;
}
int test_insertion(const uint64_t *orig_array, size_t size, struct timeval *real_diff, struct timeval *user_diff, struct timeval *sys_diff)
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
//#ifdef DEBUG
	int i;
	for (i = 0; i < size; i++) {
		printf("%" PRIu64 "\n", array[i]);
	}
//#endif
	if (array) {
		free(array);
	}
	if (cpy_array) {
		free(cpy_array);
	}
	return 0;
}

int main(int argc, char *argv[])
{
	size_t len = 10;
	uint64_t *array = NULL;
	struct timeval real_diff, user_diff, sys_diff;
	if (argc < 2) {
		fprintf(stderr, "Usage: %s filename\n", *argv);
		return 1;
	}
	load_numbers(argv[1], &array, &len);
	test_insertion(array, len, &real_diff, &user_diff, &sys_diff);
	printf("real:\t%ld.%.06ld\n", real_diff.tv_sec, real_diff.tv_usec);
	printf("user:\t%ld.%.06ld\n", user_diff.tv_sec, user_diff.tv_usec);
	printf("sys:\t%ld.%.06ld\n", sys_diff.tv_sec, sys_diff.tv_usec);
	free(array);

	return 0;
}
