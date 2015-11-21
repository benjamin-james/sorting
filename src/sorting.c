#include "sorting.h"

int insertion_sort(uint64_t *array, size_t size)
{
	size_t i, j;
	uint64_t temp;
	for (i = 1; i < size; i++) {
		temp = array[i];
		for (j = i; j > 0 && temp < array[j - 1]; j--) {
			array[j] = array[j-1];
		}
		array[j] = temp;
	}
	return 0;
}
int bubble_sort(uint64_t *array, size_t size)
{
	int i, j, swapped;
	for (i = (int)size - 1; i >= 0; i--) {
		swapped = 0;
		for (j = 0; j < i; j++) {
			if (array[j] <= array[j + 1]) {
				continue;
			}
			uint64_t temp = array[j];
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

int merge(const uint64_t *array, size_t begin, size_t middle, size_t end, uint64_t *buffer)
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
int merge_sort(uint64_t *array, size_t begin, size_t end, uint64_t *buffer)
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

int hybrid_sort(uint64_t *array, size_t begin, size_t end, uint64_t *buffer, int cutoff)
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
