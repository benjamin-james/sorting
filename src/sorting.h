#ifndef SORTING
#define SORTING

#include <stdint.h>
#include <string.h>
#include "tree.h"

#ifndef SWAP
#define SWAP(type, r, s) \
	do { \
		type t = r; \
		r = s; \
		s = t; \
	} while (0);
#endif

int insertion_sort(intmax_t *array, size_t size);
int bubble_sort(intmax_t *array, size_t size);
int merge_sort(intmax_t *array, size_t begin, size_t end, intmax_t *buffer);
int first_pivot(const intmax_t *array, size_t begin, size_t end);
int random_pivot(const intmax_t *array, size_t begin, size_t end);
int quicksort(intmax_t *array, size_t begin, size_t end, int (*choose_pivot)(const intmax_t *array, size_t begin, size_t end));
int heapsort(intmax_t *array, size_t size);
int hybrid_sort(intmax_t *array, size_t begin, size_t end, intmax_t *buffer, intptr_t cutoff);
int treesort(const intmax_t *array, size_t array_size, struct tree **t);
#endif
