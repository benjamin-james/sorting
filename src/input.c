
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#include "input.h"

int print_help(const char *program_name)
{
	fprintf(stderr, "Usage: %s [OPTIONS] [FILENAME]\n", program_name);
	fprintf(stderr, "\n");
	fprintf(stderr, "\t-h, --help     prints this message\n");
	fprintf(stderr, "\t-v, --verbose  prints the sorted array (enabled by default)\n");
	fprintf(stderr, "\t-q, --quiet    omits printing the sorted array\n");
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


int get_sorting_type(const char *arg, int *ret)
{
	if (arg == NULL) {
		goto bad;
	} else if (!strcasecmp(arg, "treesort") || !strcasecmp(arg, "tree")) {
		*ret = TREE_SORT;
	} else if (!strcasecmp(arg, "heapsort") || !strcasecmp(arg, "heap")) {
		*ret = HEAP_SORT;
	} else if (!strcasecmp(arg, "quicksort") || !strcasecmp(arg, "quick")) {
		*ret = QUICK_SORT;
	} else if (!strcasecmp(arg, "mergesort") || !strcasecmp(arg, "merge")) {
		*ret = MERGE_SORT;
	} else if (!strcasecmp(arg, "insertion sort") || !strcasecmp(arg, "insertion")) {
		*ret = INSERTION_SORT;
	} else if (!strcasecmp(arg, "bubblesort") || !strcasecmp(arg, "bubble")) {
		*ret = BUBBLE_SORT;
	} else if (!strcasecmp(arg, "hybrid sort") || !strcasecmp(arg, "hybrid")) {
		*ret = HYBRID_SORT;
	} else {
		goto bad;
	}
	return 0;
bad:
	*ret = 0;
	return -1;
}

int get_option(int character, int *sorting, bool *reg_pivot, intptr_t *cutoff, bool *print, bool *do_time, const char *program_name)
{
	int ret = 0;
	char *endptr = NULL;
	long l = 0;
	switch (character) {
	case 'c': {
		l = strtol(optarg, &endptr, 10);
		if (l > INTPTR_MAX || l <= 0 || *endptr) {
			fprintf(stderr, "Please enter a positive integer\n");
			ret = -1;
		} else {
			*cutoff = (intptr_t)l;
		}
		break;
	}
	case 'h': {
		ret = -1;
		print_help(program_name);
		break;
	}
	case 'n': {
		*do_time = 0;
		break;
	}
	case 'p': {
		if (!strcasecmp(optarg, "first")) {
			*reg_pivot = 1;
		} else if (!strcasecmp(optarg, "random")) {
		       	*reg_pivot = 0;
		} else {
			fprintf(stderr, "Unrecognized pivot type \"%s\"\n", optarg);
			ret = -1;
		}
		break;
	}
	case 'q': {
		*print = 0;
		break;
	}
	case 's': {
		ret = get_sorting_type(optarg, sorting);
		break;
	}
	case 't': {
		*do_time = 1;
		break;
	}
	case 'v': {
		*print = 1;
		break;
	}
	default: {
		ret = -1;
		print_help(program_name);
		break;
	}
	}
	return ret;
}


int do_getopt(const int argc, char *const *argv, int *sorting, char **input, bool *reg_pivot, intptr_t *cutoff, bool *print, bool *do_time)
{
	int c, option_index;
	int ret = 0;
	static struct option long_options[] = {
		{"cutoff", required_argument, 0, 'c'},
		{"help", no_argument, 0, 'h'},
		{"no-time", no_argument, 0, 'n'},
		{"pivot", required_argument, 0, 'p'},
		{"quiet", no_argument, 0, 'q'},
		{"sort", required_argument, 0, 's'},
		{"time", no_argument, 0, 't'},
		{"verbose", no_argument, 0, 'v'},
		{0, 0, 0, 0}
	};
	while (!ret && (c = getopt_long(argc, argv, "c:f:hnp:qs:tv", long_options, &option_index)) != -1) {
		ret = get_option(c, sorting, reg_pivot, cutoff, print, do_time, *argv);
	}
	if (!ret && optind < argc) {
		*input = argv[optind++];
	}
       	while (optind < argc) {
			printf("Unrecognized option \"%s\"\n", argv[optind++]);
			ret = -1;
       	}
	return ret;
}
