#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <inttypes.h>
#include <unistd.h>

#include "util.h"

int timeval_diff(struct timeval start, struct timeval end, struct timeval *diff)
{
	if (diff == NULL) {
		return -1;
	}
	if (end.tv_usec < start.tv_usec) {
		time_t usec_in_sec = (start.tv_usec - end.tv_usec) / 1000000 + 1;
		start.tv_usec -= 1000000 * usec_in_sec;
		start.tv_sec += usec_in_sec;
	}
	if (end.tv_usec - start.tv_usec > 1000000) {
		time_t usec_in_sec = (end.tv_usec - start.tv_usec) / 1000000;
		start.tv_usec += 1000000 * usec_in_sec;
		start.tv_sec -= usec_in_sec;
	}
	diff->tv_sec = end.tv_sec - start.tv_sec;
	diff->tv_usec = end.tv_usec - start.tv_usec;
	return end.tv_sec < start.tv_sec;
}
int get_clock(struct timeval *_timeval, struct rusage *_rusage)
{
	if (gettimeofday(_timeval, NULL) < 0) {
		perror("gettimeofday: ");
		return -1;
	}
	if (getrusage(RUSAGE_SELF, _rusage) < 0) {
		perror("getrusage: ");
		return -1;
	}
	return 0;
}
int dup_array(const intmax_t *array, size_t size, intmax_t **ret_array)
{
	intmax_t *temp_array = malloc(sizeof *array * size);
	if (temp_array == NULL) {
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
	size_t len = 0;
	ssize_t read = 0;
	intmax_t *array = malloc(sizeof *array);
	size_t arr_len = 0;
	size_t arr_alloc = 1;
	FILE *fp = fopen(filename, "r");
	if (fp == NULL) {
		return -1;
	}
	while ((read = getline(&line, &len, fp)) != -1) {
		if (arr_len == arr_alloc) {
			arr_alloc *= 2;
			intmax_t *tmp = realloc(array, sizeof *array * arr_alloc);
			if (tmp != NULL) {
				array = tmp;
			}
		}
		array[arr_len++] = (intmax_t)strtoll(line, NULL, 10);
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
	return 0;
}

int print_array(FILE *fp, const intmax_t *array, size_t size)
{
	size_t i;
	for (i = 0; i < size; i++) {
		fprintf(fp, "%" PRIdMAX "\n", array[i]);
	}
	return 0;
}
