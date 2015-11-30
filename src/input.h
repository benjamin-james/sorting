#ifndef INPUT_H
#define INPUT_H

#include <stdbool.h>
#include <inttypes.h>

#define MERGE_SORT 1
#define INSERTION_SORT 2
#define BUBBLE_SORT 3
#define HYBRID_SORT 4
#define HEAP_SORT 5
#define TREE_SORT 6
#define QUICK_SORT 7

int print_help(const char *program_name);

int get_sorting_type(const char *arg, int *ret);

int get_option(int character, int *sorting, char **input, bool *reg_pivot, intptr_t *cutoff, bool *print, bool *do_time, const char *program_name);

int do_getopt(const int argc, char *const *argv, int *sorting, char **input, bool *reg_pivot, intptr_t *cutoff, bool *print, bool *do_time);

#endif
