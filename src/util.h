#ifndef UTIL_H
#define UTIL_H

#include <stdint.h>
#include <sys/types.h>

int timeval_diff(struct timeval start, struct timeval end, struct timeval *diff);
int do_time(int (*sort)(uint64_t *array, size_t size), uint64_t *array, size_t size);
int load_numbers(const char *filename, uint64_t **ret, size_t *ret_len);
#endif
