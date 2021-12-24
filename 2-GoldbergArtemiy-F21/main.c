#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

int main(void)
{
	tree_t* tree = NULL;
	int data, k = 3;

	data = 29;
	tree = add_vertex(tree, data);

	data = 26;
	tree = add_vertex(tree, data);

	data = 30;
	tree = add_vertex(tree, data);

	data = 33;
	tree = add_vertex(tree, data);

	data = 32;
	tree = add_vertex(tree, data);

	data = 35;
	tree = add_vertex(tree, data);

	data = 34;
	tree = add_vertex(tree, data);

	find_vertex(tree->right->right->left, 3);
	return 0;
}