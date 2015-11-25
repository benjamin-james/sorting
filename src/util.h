#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <stdint.h>
#include <time.h>

int timespec_diff(struct timespec start, struct timespec end, struct timespec *diff);
int load_numbers(const char *filename, intmax_t **ret, size_t *ret_len);

int get_clock(struct timespec *ts);

int dup_array(const intmax_t *array, size_t size, intmax_t **ret_array);

int print_array(FILE *fp, const intmax_t *array, size_t size);

int print_bst(FILE *fp, const intmax_t *array, size_t size);
#endif
