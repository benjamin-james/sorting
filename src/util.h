#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>

int timeval_diff(struct timeval start, struct timeval end, struct timeval *diff);
int load_numbers(const char *filename, intmax_t **ret, size_t *ret_len);

int get_clock(struct timeval *end_timeval, struct rusage *start_rusage);

int dup_array(const intmax_t *array, size_t size, intmax_t **ret_array);

int print_array(FILE *fp, const intmax_t *array, size_t size);

int print_bst(FILE *fp, const intmax_t *array, size_t size);
#endif
