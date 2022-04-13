#pragma once
#define Tr 2 
#define MIN (Tr - 1)
#define MAX (2 * Tr - 1) 
#define MAX_CHILDREN (2 * Tr)
#define TRUE 1
#define FALSE 0

typedef enum Key_status { SEARCH_FAIL, SUCCESS, LESS_KEYS } Key_status;

typedef struct Node {
	struct Node* children[MAX_CHILDREN];
	int keys[MAX];
	int keys_num;
}Node;

Node* allocate();
int position(int key, int* key_arr, int n);
Key_status deleting(Node* node, int key);
void deleting_node(int key);
void split(Node* upnode, int index);
void not_full_check(Node* node, int data);
void inserting_node(int data);
int searching(int data);
void set_position(int x, int y);
int calculate_width(Node* node);
void printing(Node* node, int y, int width);
void print_tree(int y);