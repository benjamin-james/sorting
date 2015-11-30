#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <inttypes.h>

#include "util.h"

int remove_newline(char *str)
{
	int len = strlen(str);
	if (str[len - 1] == '\n') {
		str[len - 1] = 0;
		return 1;
	}
	return 0;
}

int timespec_diff(struct timespec start, struct timespec end, struct timespec *diff)
{
	if (diff == NULL) {
		return -1;
	}
	if (end.tv_nsec < start.tv_nsec) {
		long nsec_in_sec = (start.tv_nsec - end.tv_nsec) / 1000000000 + 1;
		start.tv_nsec -= 1000000000 * nsec_in_sec;
		start.tv_sec += nsec_in_sec;
	}
	if (end.tv_nsec - start.tv_nsec > 1000000000) {
		long nsec_in_sec = (end.tv_nsec - start.tv_nsec) / 1000000000;
		start.tv_nsec += 1000000000 * nsec_in_sec;
		start.tv_sec -= nsec_in_sec;
	}
	diff->tv_sec = end.tv_sec - start.tv_sec;
	diff->tv_nsec = end.tv_nsec - start.tv_nsec;
	return 0;
}
int get_clock(struct timespec *ts)
{
	return clock_gettime(CLOCK_MONOTONIC, ts);
}
int dup_array(const intmax_t *array, size_t size, intmax_t **ret_array)
{
	intmax_t *temp_array = malloc(sizeof *array * size);
	if (temp_array == NULL) {
		perror("malloc");
		return -1;
	}
	memcpy(temp_array, array, sizeof *array * size);
	if (ret_array) {
		*ret_array = temp_array;
	}
	return 0;
}

int load_numbers(const char *filename, intmax_t **ret, size_t *ret_len)
{
	char *line = NULL;
	char *endptr = NULL;
	size_t len = 0;
	ssize_t read = 0;
	intmax_t *array = malloc(sizeof *array);
	size_t arr_len = 0;
	size_t arr_alloc = 1;
	int ret_val = 0;
	FILE *fp = fopen(filename, "r");
	if (fp == NULL) {
		perror(filename);
		return -1;
	}
	while ((read = getline(&line, &len, fp)) != -1) {
		if (arr_len == arr_alloc) {
			arr_alloc *= 2;
			intmax_t *tmp = realloc(array, sizeof *array * arr_alloc);
			if (tmp) {
				array = tmp;
			} else {
				perror("realloc");
			}
		}

		array[arr_len++] = strtoimax(line, &endptr, 10);
		if (*endptr) {
			remove_newline(line);
			fprintf(stderr, "\"%s\" is not a valid integer\n", line);
			ret_val = -1;
			break;
		}
	}
	fclose(fp);
	if (line) {
		free(line);
	}
	if (ret) {
		*ret = array;
	}
	if (ret_len) {
		*ret_len = arr_len;
	}
	return ret_val;
}

int print_array(FILE *fp, const intmax_t *array, size_t size)
{
	size_t i;
	for (i = 0; i < size; i++) {
		fprintf(fp, "%" PRIdMAX "\n", array[i]);
	}
	return 0;
}
