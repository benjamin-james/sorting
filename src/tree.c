#include <stdlib.h>
#include "tree.h"

int tree_new(struct tree **ret)
{
	struct tree *t = malloc(sizeof *t);
	t->left = NULL;
	t->right = NULL;
	t->item = -1;
	t->set = 0;
	*ret = t;
	return 0;
}

int tree_insert(struct tree *t, intmax_t item)
{
	if (t->set == 0) {
		t->item = item;
		t->set = 1;
		return 0;
	}
	if (item < t->item) {
		if (t->left == NULL) {
			tree_new(&t->left);
		}
		return tree_insert(t->left, item);
	} else if (item > t->item) {
		if (t->right == NULL) {
			tree_new(&t->right);
		}
		return tree_insert(t->right, item);
	}
	return -2;
}

int tree_free(struct tree *t)
{
	if (t != NULL) {
		tree_free(t->left);
		tree_free(t->right);
		free(t);
	}
	return 0;
}

int print_tree(FILE *fp, const struct tree *t)
{
	if (t == NULL) {
		return 0;
	}
	print_tree(fp, t->left);
	fprintf(fp, "%" PRIdMAX "\n", t->item);
	print_tree(fp, t->right);
	return 0;
}
