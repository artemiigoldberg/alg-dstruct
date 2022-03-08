#include <stdlib.h>
#include <stdio.h>
#include "Tree.h"

static RBTree* NIL = NULL;

void init_tree(RBTree** node) {
    if (NIL == NULL) {
        NIL = (RBTree*)malloc(sizeof(RBTree));

        if (NIL == NULL)
            return;

        NIL->right = NIL;
        NIL->parent = NIL;
        NIL->left = NIL;
        NIL->data = 0;
    }

    *node = NIL;
}

void insert_node(RBTree** node, int data) {
    RBTree** cur, * parent;
    cur = node;
    parent = NIL;

    while (*cur != NIL) {
        parent = (*cur);
        if ((*cur)->data == data)
            return;
        cur = data < (*cur)->data ? &((*cur)->left) : &((*cur)->right);
    }

    RBTree* new_node = (RBTree*)malloc(sizeof(RBTree));

    if (new_node == NULL)
        return;

    new_node->data = data;
    new_node->parent = parent;
    new_node->left = NIL;
    new_node->right = NIL;
    new_node->color = RED;

    if (parent != NIL) {
        if (data < parent->data)
            parent->left = new_node;
        else
            parent->right = new_node;
    }
    else
        (*cur) = new_node;

    fix_balance(node, new_node);
}

void fix_balance(RBTree** node, RBTree* new_node) {
    RBTree* cur = new_node;

    while (cur != *(node) && cur->parent->color == RED) {
        if (cur->parent == cur->parent->parent->left) {
            RBTree* ptr = cur->parent->parent->right;

            if (ptr->color == RED) {
                cur->parent->color = BLACK;
                ptr->color = BLACK;
                cur->parent->parent->color = RED;
                cur = cur->parent->parent;
            }
            else {
                if (cur == cur->parent->right) {
                    cur = cur->parent;
                    rotate_left(node, cur);
                }

                cur->parent->color = BLACK;
                cur->parent->parent->color = RED;
                rotate_right(node, cur->parent->parent);
            }
        }
        else {
            RBTree* ptr = cur->parent->parent->left;

            if (ptr->color == RED) {
                cur->parent->color = BLACK;
                ptr->color = BLACK;
                cur->parent->parent->color = RED;
                cur = cur->parent->parent;
            }
            else {
                if (cur == cur->parent->left) {
                    cur = cur->parent;
                    rotate_right(node, cur);
                }

                cur->parent->color = BLACK;
                cur->parent->parent->color = RED;
                rotate_left(node, cur->parent->parent);
            }
        }
    }
    (*node)->color = BLACK;
}

void rotate_left(RBTree** node, RBTree* cur) {
    RBTree* ptr = cur->right;
    cur->right = ptr->left;

    if (ptr->left != NIL)
        ptr->left->parent = cur;

    if (ptr != NIL)
        ptr->parent = cur->parent;

    if (cur->parent != NIL) {
        if (cur == cur->parent->left)
            cur->parent->left = ptr;
        else
            cur->parent->right = ptr;
    }
    else
        (*node) = ptr;

    ptr->left = cur;

    if (cur != NIL)
        cur->parent = ptr;
}

void rotate_right(RBTree** node, RBTree* cur) {
    RBTree* ptr = cur->left;
    cur->left = ptr->right;

    if (ptr->right != NIL)
        ptr->right->parent = cur;

    if (ptr != NIL)
        ptr->parent = cur->parent;

    if (cur->parent != NIL) {
        if (cur == cur->parent->right)
            cur->parent->right = ptr;
        else
            cur->parent->left = ptr;
    }
    else {
        (*node) = ptr;
    }

    ptr->right = cur;

    if (cur != NIL)
        cur->parent = ptr;
}

void fix_after_delete(RBTree** tree_p, RBTree* node) {
    while (node != (*tree_p)->parent && node->color == BLACK) {
        if (node->parent->right != NIL && node == node->parent->left) {
            RBTree* cur = node->parent->right;

            if (cur->color == RED) {
                cur->color = BLACK;
                node->parent->color = RED;
                rotate_left(tree_p, node->parent);
                cur = node->parent->right;
            }

            if (cur->left != NIL && cur->right != NIL && cur->left->color == BLACK && cur->right->color == BLACK) {
                cur->color = RED;
                node = node->parent;
            }
            else {

                if (cur->left != NIL && cur->right != NIL && cur->right->color == BLACK) {
                    cur->left->color = BLACK;
                    cur->color = RED;
                    rotate_right(tree_p, cur);
                    cur = node->parent->right;
                }

                if (cur->right != NIL) {
                    cur->color = node->parent->color;
                    node->parent->color = BLACK;
                    cur->right->color = BLACK;
                    rotate_left(tree_p, node->parent);
                }

                node = (*tree_p)->parent;
            }
            continue;
        }
        else
            if (node->parent->left != NIL) {
                RBTree* cur = node->parent->left;

                if (cur->color == RED) {
                    cur->color = BLACK;
                    node->parent->color = RED;
                    rotate_right(tree_p, node->parent);
                    cur = node->parent->left;
                }

                if (cur->left != NIL && cur->right != NIL && cur->right->color == BLACK && cur->left->color == BLACK) {
                    cur->color = RED;
                    node = node->parent;
                }
                else {

                    if (cur->left != NIL && cur->right != NIL && cur->left->color == BLACK) {
                        cur->right->color = BLACK;
                        cur->color = RED;
                        rotate_left(tree_p, cur);
                        cur = node->parent->left;
                    }

                    if (cur->left != NIL) {
                        cur->color = node->parent->color;
                        node->parent->color = BLACK;
                        cur->left->color = BLACK;
                        rotate_right(tree_p, node->parent);
                    }
                    node = (*tree_p)->parent;
                }
                continue;
            }
        break;
    }

    node->color = BLACK;
}

void delete_node(RBTree** tree_p, int data) {
    RBTree* tree = *tree_p;
    RBTree* cur = tree;
    RBTree* del_node = NIL;

    while (cur != NIL)
        if (data == cur->data) {
            del_node = cur;
            break;
        }
        else
            cur = data < cur->data ? cur->left : cur->right;

    if (del_node == NIL)
        return;

    RBTree* swap;

    if (del_node->left == NIL || del_node->right == NIL)
        swap = del_node;
    else {
        swap = del_node->right;

        while (swap->left != NIL)
            swap = swap->left;
    }

    RBTree* swap_child;

    if (swap->left != NIL)
        swap_child = swap->left;
    else
        swap_child = swap->right;

    if (swap_child != NIL)
        swap_child->parent = swap->parent;

    if (swap->parent != NIL) {
        if (swap == swap->parent->left)
            swap->parent->left = swap_child;
        else
            swap->parent->right = swap_child;
    }
    else
        tree->parent = swap_child;

    if (swap != del_node)
        del_node->data = swap->data;

    if (swap->color == BLACK && swap_child != NIL)
        //         fix_balance(&tree, swap_child);
        fix_after_delete(tree_p, swap_child);

    if (swap == tree) {
        *tree_p = swap_child;
    }

    if (swap != NIL)
        free(swap);
}

void merge_pass(RBTree** tree, RBTree* node) {
    if (node == NIL)
        return;

    merge_pass(tree, node->left);
    insert_node(tree, node->data);
    merge_pass(tree, node->right);
}

RBTree* merge(RBTree* tree1, RBTree* tree2, int data) {
    RBTree* merge_tree;

    merge_pass(&merge_tree, tree1);
    merge_pass(&merge_tree, tree2);
    insert_node(&merge_tree, data);
    return merge_tree;
}

int search_tree(RBTree* tree, int val) {
    while (tree != NIL) {
        if (tree->data < val)
            tree = tree->right;
        else
            if (tree->data > val)
                tree = tree->left;
            else
                return 1;
    }

    return 0;
}

void print_tree(RBTree* node, int node_number) {
    int i;

    if (node != NIL) {
        print_tree(node->right, node_number + 1);

        for (i = 0; i < node_number; i++)
            printf("    ");

        if (node->color == RED)
            printf("\033[41m%4d\033[0m", node->data);
        else
            printf("%4d", node->data);

        print_tree(node->left, node_number + 1);
    }
    else
        printf("\n");
}

int empty_tree_check(RBTree* node) {
    return (node == NIL ? TRUE : FALSE);
}

void delete_tree(RBTree* node) {
    if (node != NIL) {
        delete_tree(node->left);
        delete_tree(node->right);
        free(node);
    }
}
