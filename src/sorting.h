#ifndef SORTING
#define SORTING

#include <stdint.h>
#include <string.h>

int insertion_sort(intmax_t *array, size_t size);
int bubble_sort(intmax_t *array, size_t size);
int merge_sort(intmax_t *array, size_t begin, size_t end, intmax_t *buffer);
int first_pivot(const intmax_t *array, size_t begin, size_t end);
int random_pivot(const intmax_t *array, size_t begin, size_t end);
int quicksort(intmax_t *array, size_t begin, size_t end, int (*choose_pivot)(const intmax_t *array, size_t begin, size_t end));
int heapsort(intmax_t *array, size_t size);
int treesort(intmax_t *array, size_t size);
int hybrid_sort(intmax_t *array, size_t begin, size_t end, intmax_t *buffer, int cutoff);
#endif
