#include <stdbool.h>
#include <stdlib.h>
#include "sorting.h"

int treesort(const intmax_t *array, size_t array_size, struct tree **tree)
{
	size_t i;
	int ret = 0;
	struct tree *t = NULL;
	tree_new(&t);
	for (i = 0; ret == 0 && i < array_size; i++) {
		ret = tree_insert(t, array[i]);
	}
	if (tree) {
		*tree = t;
	}
	return ret;
}

int sift_down(intmax_t *array, intptr_t start, intptr_t end)
{
	intptr_t root = start;
	while (root * 2 + 1 < end) {
		intptr_t child = 2 * root + 1;
		if (child + 1 < end && array[child] < array[child+1]) {
			child++;
		}
		if (array[root] < array[child]) {
			SWAP(intmax_t, array[child], array[root]);
			root = child;
		} else {
			break;
		}
	}
	return 0;
}

int heapsort(intmax_t *array, size_t size)
{
	intptr_t start, end;
	for (start = (size - 2)/2; start >= 0; start--) {
		sift_down(array, start, size);
	}
	for (end = size - 1; end > 0; end--) {
		SWAP(intmax_t, array[end], array[0]);
		sift_down(array, 0, end);
	}
	return 0;
}
int first_pivot(const intmax_t *array, size_t begin, size_t end)
{
	return begin;
}

int random_pivot(const intmax_t *array, size_t begin, size_t end)
{
	return (rand() % (end - begin)) + begin;
}

int quicksort(intmax_t *array, size_t begin, size_t end, int (*choose_pivot)(const intmax_t *array, size_t begin, size_t end))
{
	if (begin >= end) {
		return 0;
	}
	size_t pivot_index = choose_pivot(array, begin, end);
	intmax_t pivot = array[pivot_index];
	size_t left = begin;
	size_t right = end;
	while (left <= right) {
		while (array[left] < pivot) {
			left++;
		}
		while (array[right] > pivot) {
			right--;
		}
		if (left <= right) {
			SWAP(intmax_t, array[left], array[right]);
			left++;
			right--;
		}
	}
	quicksort(array, begin, pivot_index, choose_pivot);
	quicksort(array, pivot_index + 1, end, choose_pivot);
	return 0;
}

int insertion_sort(intmax_t *array, size_t size)
{
	size_t i, j;
	intmax_t temp;
	for (i = 1; i < size; i++) {
		temp = array[i];
		for (j = i; j > 0 && temp < array[j - 1]; j--) {
			array[j] = array[j-1];
		}
		array[j] = temp;
	}
	return 0;
}

int bubble_sort(intmax_t *array, size_t size)
{
	int i, j, swapped;
	for (i = (int)size - 1; i >= 0; i--) {
		swapped = 0;
		for (j = 0; j < i; j++) {
			if (array[j] <= array[j + 1]) {
				continue;
			}
			intmax_t temp = array[j];
			array[j] = array[j + 1];
			array[j + 1] = temp;
			swapped = 1;

		}
		if (!swapped) {
			break;
		}

	}
	return 0;
}

int merge(const intmax_t *array, size_t begin, size_t middle, size_t end, intmax_t *buffer)
{
	size_t i, left = begin, right = middle;
	for (i = begin; i < end; i++) {
		if (left < middle && (right >= end || array[left] <= array[right])) {
			buffer[i] = array[left++];
		} else {
			buffer[i] = array[right++];
		}
	}
	return 0;
}

int merge_sort(intmax_t *array, size_t begin, size_t end, intmax_t *buffer)
{
	size_t middle = (end - begin) / 2;
	if (end - begin < 2) {
		return 0;
	}
	middle = (end + begin) / 2;
	merge_sort(array, begin, middle, buffer);
	merge_sort(array, middle, end, buffer);
	merge(array, begin, middle, end, buffer);
	memcpy(array + begin, buffer + begin, (end - begin) * sizeof *array);
	return 0;
}

int hybrid_sort(intmax_t *array, size_t begin, size_t end, intmax_t *buffer, intptr_t cutoff)
{
	size_t middle = (end + begin) / 2;
	if (end - begin <= (size_t)cutoff) {
		return insertion_sort(array + begin, end - begin);
	}
	hybrid_sort(array, begin, middle, buffer, cutoff);
	hybrid_sort(array, middle, end, buffer, cutoff);
	merge(array, begin, middle, end, buffer);
	memcpy(array + begin, buffer + begin, (end - begin) * sizeof *array);
	return 0;
}
