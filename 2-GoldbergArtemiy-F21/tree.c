#include <stdio.h>
#include "tree.h"

tree_t* add_vertex(tree_t* tree, int new_data) {
	if (tree == NULL) {
		tree = (tree_t*)malloc(sizeof(tree_t));
		tree->parent = NULL;
		tree->data = new_data;
		tree->size = 1;
		tree->left = tree->right = NULL;
		return tree;
	}
	else
		if (new_data < tree->data) {
			tree->left = add_vertex(tree->left, new_data);
			tree->left->parent = tree;
		}
		else {
			tree->right = add_vertex(tree->right, new_data);
			tree->right->parent = tree;
		}

	tree->size++;
	return tree;
}

int find_serial(tree_t* tree) {
	if (tree == NULL)
		return 0;

	tree_t* parent;
	int serial;

	if (tree->parent == NULL)
		return 1;

	if (tree->left != NULL)
		serial = tree->left->size;
	else
		serial = 1;

	while (tree->parent != NULL)
	{
		parent = tree->parent;

		if (tree == parent->right)
			if (parent->left != NULL)
				serial += parent->left->size + 1;
			else
				serial += 1;
		else
			serial++;

		tree = parent;
	}

	return serial;
}

void find_vertex(tree_t* tree, int k) {
	int serial = find_serial(tree) - k;

	if (serial <= 0) {
		printf("Error");
		return;
	}

	while (tree->parent != NULL) {
		tree = tree->parent;
	}

	while (serial > 1) {
		if (tree->left != NULL)
			if (tree->left->size + 1 >= serial) {
				serial--;
				tree = tree->left;
			}
			else {
				serial -= tree->left->size;
				tree = tree->right;
			}
		else {
			serial--;
			tree = tree->right;
		}		
	}

	printf("%d", tree->data);
	return;
	
}
