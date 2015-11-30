#include <ctype.h>
#include <errno.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "sorting.h"
#include "test.h"
#include "util.h"

static char *PROGRAMNAME = NULL;

int print_help(void)
{
	fprintf(stderr, "Usage: %s [OPTIONS]\n", PROGRAMNAME);
	fprintf(stderr, "\n");
	fprintf(stderr, "\t-h, --help     prints this message\n");
	fprintf(stderr, "\t-v, --verbose  prints the sorted array (enabled by default)\n");
	fprintf(stderr, "\t-q, --quiet    omits printing the sorted array\n");
	fprintf(stderr, "\t-f, --file     specify the filename of the list to sort (default stdin)\n");
	fprintf(stderr, "\t-s, --sort     specify the sort to be done, consisting of:\n");
	fprintf(stderr, "\t                   quicksort, mergesort, bubblesort, insertion sort,\n");
	fprintf(stderr, "\t                   treesort, heapsort, hybridsort (hybrid mergesort-insertion sort)\n");
	fprintf(stderr, "\t-t, --time     print the time it took to sort the array\n");
	fprintf(stderr, "\t-n, --no-time  don't print the time it took to sort the array (default)\n");
	fprintf(stderr, "\t-c, --cutoff   specify the cutoff in hybrid sort to switch from hybrid to insertion sort (default 1)\n");
	fprintf(stderr, "\t-p, --pivot    specify whether the pivot in quicksort is \"first\" or \"random\" pivot element (default \"first\")\n");
	fprintf(stderr, "\n");
	return 0;
}

int is_uint(const char *str)
{
	if (!*str) {
		return 0;
	}
	for (;*str; str++) {
		if (!isdigit(*str)) {
			return 0;
		}
	}
	return 1;
}

int get_sorting(const char *arg, char **ret)
{
	int r = 0;
	if (arg == NULL) {
		*ret = NULL;
		r = -1;
	} else if (!strcasecmp(arg, "treesort") || !strcasecmp(arg, "tree")) {
		*ret = strdup("tree");
	} else if (!strcasecmp(arg, "heapsort") || !strcasecmp(arg, "heap")) {
		*ret = strdup("heap");
	} else if (!strcasecmp(arg, "quicksort") || !strcasecmp(arg, "quick")) {
		*ret = strdup("quick");
	} else if (!strcasecmp(arg, "mergesort") || !strcasecmp(arg, "merge")) {
		*ret = strdup("merge");
	} else if (!strcasecmp(arg, "insertion sort") || !strcasecmp(arg, "insertion")) {
		*ret = strdup("insertion");
	} else if (!strcasecmp(arg, "bubblesort") || !strcasecmp(arg, "bubble")) {
		*ret = strdup("bubble");
	} else if (!strcasecmp(arg, "hybrid sort") || !strcasecmp(arg, "hybrid")) {
		*ret = strdup("hybrid");
	} else {
		*ret = NULL;
		r = -1;
	}
	return r;
}

int main(int argc, char **argv)
{
	size_t len = 0;
	intmax_t *array = NULL;
	struct timespec diff;
	static int print = 1;
	static int do_time = 0;
	int c, option_index;
	int cutoff = 1;
	int reg_pivot = 1;
	char default_input[] = "/dev/stdin";
	char *input = default_input;
	char *sort = NULL;
	PROGRAMNAME = *argv;
	static struct option long_options[] = {
		{"verbose", no_argument, &print, 1},
		{"quiet", no_argument, &print, 0},
		{"sort", required_argument, 0, 's'},
		{"time", no_argument, &do_time, 1},
		{"no-time", no_argument, &do_time, 0},
		{"file", required_argument, 0, 'f'},
		{"cutoff", required_argument, 0, 'c'},
		{"pivot", required_argument, 0, 'p'},
		{"help", no_argument, 0, 'h'},
		{0, 0, 0, 0}
	};
	srand(time(NULL));
	while ((c = getopt_long(argc, argv, "vqhtnc:p:s:f:", long_options, &option_index)) != -1) {
		unsigned long ul = 0;
		switch (c) {
		case 0:
		case 1:
			break;
		case 's':
			if (get_sorting(optarg, &sort) < 0) {
				goto exit_failure;
			}
			break;
		case 'p':
			if (optarg == NULL) {
				goto pivot_failure;
			} else if (!strcasecmp(optarg, "first")) {
				reg_pivot = 1;
			} else if (!strcasecmp(optarg, "random")) {
				reg_pivot = 0;
			} else {
				goto pivot_failure;
			}
			break;
		pivot_failure:
			fprintf(stderr, "Unknown option: %s\n", optarg);
			goto exit_failure;

		case 'c':
			errno = 0;
			if (!is_uint(optarg)) {
				goto cutoff_failure;
			}
			ul = strtoul(optarg, NULL, 10);
			cutoff = (int)ul;
			if (errno || ul > INT32_MAX) {
				goto cutoff_failure;
			}
			break;
		cutoff_failure:
			fprintf(stderr, "Please input a positive integer.\n");
			goto exit_failure;
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
        if (!strcmp(sort, "tree")) {
		test_treesort(array, len, print, &diff);
	} else if (!strcmp(sort, "heap")) {
		test_heapsort(array, len, print, &diff);
	} else if (!strcmp(sort, "quick")) {
		if (reg_pivot) {
			test_quicksort(array, len, first_pivot, print, &diff);
		} else {
			test_quicksort(array, len, random_pivot, print, &diff);
		}
	} else if (!strcmp(sort, "merge")) {
		test_mergesort(array, len, print, &diff);
	} else if (!strcmp(sort, "insertion")) {
		test_insertion_sort(array, len, print, &diff);
	} else if (!strcmp(sort, "bubble")) {
		test_bubble_sort(array, len, print, &diff);
	} else if (!strcmp(sort, "hybrid")) {
		test_hybrid_sort(array, len, cutoff, print, &diff);
	} else {
		goto exit_failure;
	}
	if (do_time) {
		printf("time:\t%ld.%.09ld\n", diff.tv_sec, diff.tv_nsec);
	}
	free(array);
	free(sort);
	return 0;
exit_failure:
	if (array) {
		free(array);
	}
	if (sort) {
		free(sort);
	}
	print_help();
	return 1;
}
