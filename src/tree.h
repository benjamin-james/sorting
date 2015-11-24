#ifndef TREE_H
#define TREE_H

#include <stdbool.h>
#include <inttypes.h>
#include <stdio.h>
#include <string.h>

struct tree {
	struct tree *left, *right;
	intmax_t item;
	bool set;
};

int tree_new(struct tree **ret);
int tree_insert(struct tree *t, intmax_t item);
int tree_free(struct tree *t);
int print_tree(FILE *fp, const struct tree *t);

#endif
