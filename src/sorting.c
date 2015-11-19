#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <fcntl.h>
#include <sys/resource.h>
#include <inttypes.h>
#include <unistd.h>

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
int do_time(int (*sort)(uint64_t *array, size_t size), uint64_t *array, size_t size)
{
	struct timeval start_timeval, end_timeval, diff_real, diff_user, diff_sys;
	struct rusage start_rusage, end_rusage;
	if (gettimeofday(&start_timeval, NULL) < 0) {
		perror("gettimeofday: ");
		return -1;
	}
	if (getrusage(RUSAGE_SELF, &start_rusage) < 0) {
		perror("getrusage: ");
		return -1;
	}
	int i = sort(array, size);
	if (gettimeofday(&end_timeval, NULL) < 0) {
		perror("gettimeofday: ");
		return -1;
	}
	if (getrusage(RUSAGE_SELF, &end_rusage) < 0) {
		perror("getrusage: ");
		return -1;
	}
	timeval_diff(start_timeval, end_timeval, &diff_real);
	timeval_diff(start_rusage.ru_utime, end_rusage.ru_utime, &diff_user);
	timeval_diff(start_rusage.ru_stime, end_rusage.ru_stime, &diff_sys);
	printf("real:\t %ld.%.06ld\n", (long int) diff_real.tv_sec, (long int) diff_real.tv_usec);
	printf("user:\t %ld.%.06ld\n", (long int) diff_user.tv_sec, (long int) diff_user.tv_usec);
	printf("sys:\t %ld.%.06ld\n", (long int) diff_sys.tv_sec, (long int) diff_sys.tv_usec);
	return 0;
}

int foosort(uint64_t *array, size_t size)
{
	int i, j = 1;
	for (i = 0; i < size; i++) {
		printf("Number: %" PRIu64 "\n", array[i]);
	}
	return j;
}

int load_numbers(const char *filename, uint64_t **ret, size_t *ret_len)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read = 0;
	uint64_t *array = malloc(sizeof *array);
	size_t arr_len = 0;
	size_t arr_alloc = 1;
	FILE *fp = fopen(filename, "r");
	if (fp == NULL) {
		return -1;
	}
	while ((read = getline(&line, &len, fp)) != -1) {
		if (arr_len == arr_alloc) {
			arr_alloc *= 2;
			uint64_t *tmp = realloc(array, sizeof *array * arr_alloc);
			if (tmp != NULL) {
				array = tmp;
			}
		}
		array[arr_len++] = (uint64_t)strtoll(line, NULL, 10);
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

int main(int argc, char *argv[])
{
	size_t len = 10;
	uint64_t *array = NULL;
	if (argc < 2) {
		fprintf(stderr, "Usage: %s filename\n", *argv);
		return 1;
	}
	load_numbers(argv[1], &array, &len);
	do_time(foosort, array, len);
	free(array);
	return 0;
}
