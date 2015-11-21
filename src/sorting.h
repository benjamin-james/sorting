#ifndef SORTING
#define SORTING

#include <stdint.h>
#include <string.h>

int insertion_sort(uint64_t *array, size_t size);
int bubble_sort(uint64_t *array, size_t size);
int merge_sort(uint64_t *array, size_t begin, size_t end, uint64_t *buffer);
int quicksort(uint64_t *array, size_t size, int (*choose_pivot)(int begin, int end));
int heapsort(uint64_t *array, size_t size);
int treesort(uint64_t *array, size_t size);
int hybrid_sort(uint64_t *array, size_t begin, size_t end, uint64_t *buffer, int cutoff);
#endif
