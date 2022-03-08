#pragma once

#define TRUE 1
#define FALSE 0
typedef enum { RED, BLACK } Color;

typedef struct RBTree {
    int data;
    struct RBTree* parent;
    struct RBTree* left;
    struct RBTree* right;
    Color color;
} RBTree;

void init_tree(RBTree** Node);
void insert_node(RBTree** Node, int Data);
void fix_balance(RBTree** Node, RBTree* New_Node);
void rotate_left(RBTree** Node, RBTree* Current);
void rotate_right(RBTree** Node, RBTree* Current);
void fix_after_delete(RBTree** tree_p, RBTree* node);
void delete_node(RBTree** tree_p, int data);
void merge_pass(RBTree** tree, RBTree* node);
RBTree* merge(RBTree* tree1, RBTree* tree2, int data);
int search_tree(RBTree* tree, int val);
void print_tree(RBTree* Node, int l);
int empty_tree_check(RBTree* Node);
void delete_tree(RBTree* Node);
