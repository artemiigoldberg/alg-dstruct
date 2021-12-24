#pragma once

struct tree_t {
	struct tree_t* left;
	struct tree_t* right;
	int data;
	int size;
	struct tree_t* parent;
};

typedef struct tree_t tree_t;

tree_t* add_vertex(tree_t* tree, int new_data);
int find_serial(tree_t* tree);
void find_vertex(tree_t* tree, int k);