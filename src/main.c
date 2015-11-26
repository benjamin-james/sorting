#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "test.h"
#include "util.h"

#define PROGRAMNAME "sorting"

int print_help(void)
{
	fprintf(stderr, "Usage: %s -vqfh [filename]\n", PROGRAMNAME);
	fprintf(stderr, "\n");
	fprintf(stderr, "\t-v            prints the sorted array\n");
	fprintf(stderr, "\t-q            omits printing the sorted array\n");
	fprintf(stderr, "\t-f [filename] gets the filename of the list to sort\n");
	fprintf(stderr, "\t-h            print this message\n");
	fprintf(stderr, "\n");
	return 0;
}

int main(int argc, char **argv)
{
	size_t len = 0;
	intmax_t *array = NULL;
	struct timespec diff;
	static int print = 1;
	static int do_time = 0;
	int c, option_index;
	char default_input[] = "/dev/stdin";
	char *input = default_input;
	static struct option long_options[] = {
		{"verbose", no_argument, &print, 1},
		{"quiet", no_argument, &print, 0},
		{"time", no_argument, &do_time, 1},
		{"no-time", no_argument, &do_time, 0},
		{"file", required_argument, 0, 'f'},
		{"help", no_argument, 0, 'h'},
		{0, 0, 0, 0}
	};
	srand(time(NULL));
	while ((c = getopt_long(argc, argv, "vqhtnf:", long_options, &option_index)) != -1) {
		switch (c) {
		case 0:
		case 1:
			break;
		case 'f':
			input = optarg;
			break;
		case 'v':
			print = 1;
			break;
		case 'q':
			print = 0;
			break;
		case 't':
			do_time = 1;
			break;
		case 'n':
			do_time = 0;
			break;
		case 'h':
		default:
			goto exit_failure;
		}
	}
	load_numbers(input, &array, &len);
	test_mergesort(array, len, print, &diff);
	if (do_time) {
		printf("time:\t%ld.%.09ld\n", diff.tv_sec, diff.tv_nsec);
	}
	free(array);
	return 0;
exit_failure:
	if (array) {
		free(array);
	}
	print_help();
	return 1;
}
