#ifndef TEST_H
#define TEST_H

#include <stdbool.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>

int test_treesort(const intmax_t *orig_array, size_t size, bool print, struct timeval *real_diff, struct timeval *user_diff, struct timeval *sys_diff);

int test_heapsort(const intmax_t *orig_array, size_t size, bool print, struct timeval *real_diff, struct timeval *user_diff, struct timeval *sys_diff);

int test_quicksort(const intmax_t *orig_array, size_t size, bool print, struct timeval *real_diff, struct timeval *user_diff, struct timeval *sys_diff);

int test_mergesort(const intmax_t *orig_array, size_t size, bool print, struct timeval *real_diff, struct timeval *user_diff, struct timeval *sys_diff);

int test_insertion_sort(const intmax_t *orig_array, size_t size, bool print, struct timeval *real_diff, struct timeval *user_diff, struct timeval *sys_diff);
int test_bubble_sort(const intmax_t *orig_array, size_t size, bool print, struct timeval *real_diff, struct timeval *user_diff, struct timeval *sys_diff);

int test_hybrid_sort(const intmax_t *orig_array, size_t size, int cutoff, bool print, struct timeval *real_diff, struct timeval *user_diff, struct timeval *sys_diff);
#endif
