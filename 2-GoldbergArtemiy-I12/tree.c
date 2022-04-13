#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>
#include "tree.h"

Node* root;

Node* allocate() {
	Node* node = malloc(sizeof(Node));

	if (node != NULL) {
		for (int i = 0; i < MAX_CHILDREN; i++)
			node->children[i] = NULL;

		node->keys_num = 0;
	}

	return node;
}

int position(int key, int* key_arr, int n) {
	int pos = 0;

	while (pos < n && key > key_arr[pos])
		pos++;

	return pos;
}


Key_status deleting(Node* node, int key) {
	Key_status value;
	
	int pos, i, pivot;

	Node* lptr;
	Node* rptr;

	if (node == NULL) 
		return SEARCH_FAIL;

	int n = node->keys_num;
	int* key_arr = node->keys;
	Node** p = node->children;
	int pos = position(key, key_arr, n);

	if (p[0] == NULL) {
		if (pos == n || key < key_arr[pos]) 
			return SEARCH_FAIL;
	
		for (i = pos + 1; i < n; i++){
			key_arr[i - 1] = key_arr[i];
			p[i] = p[i + 1];
		}

		return --node->keys_num >= (node == root ? 1 : MIN) ? SUCCESS : LESS_KEYS;
	}

	if (pos < n && key == key_arr[pos]) {
		Node* qp = p[pos];
		Node* qp1;
		int nkey;

		while (TRUE) {
			nkey = qp->keys_num;
			qp1 = qp->children[nkey];

			if (qp1 == NULL) 
				break;
			
			qp = qp1;
		}

		key_arr[pos] = qp->keys[nkey - 1];
		qp->keys[nkey - 1] = key;
	}

	value = deleting(p[pos], key);

	if (value != LESS_KEYS) 
		return value;
	
	if (pos > 0 && p[pos - 1]->keys_num > MIN) {
		pivot = pos - 1;
		lptr = p[pivot];
		rptr = p[pos];
		rptr->children[rptr->keys_num + 1] = rptr->children[rptr->keys_num];

		for (i = rptr->keys_num; i > 0; i--) {
			rptr->keys[i] = rptr->keys[i - 1];
			rptr->children[i] = rptr->children[i - 1];
		}

		rptr->keys_num++;
		rptr->keys[0] = key_arr[pivot];
		rptr->children[0] = lptr->children[lptr->keys_num];
		key_arr[pivot] = lptr->keys[--lptr->keys_num];

		return SUCCESS;
	}

	if (pos < n && p[pos + 1]->keys_num > MIN) {
		pivot = pos;
		lptr = p[pivot];
		rptr = p[pivot + 1];
		lptr->keys[lptr->keys_num] = key_arr[pivot];
		lptr->children[lptr->keys_num + 1] = rptr->children[0];
		key_arr[pivot] = rptr->keys[0];
		lptr->keys_num++;
		rptr->keys_num--;

		for (i = 0; i < rptr->keys_num; i++) {
			rptr->keys[i] = rptr->keys[i + 1];
			rptr->children[i] = rptr->children[i + 1];
		}

		rptr->children[rptr->keys_num] = rptr->children[rptr->keys_num + 1];

		return SUCCESS;
	}

	if (pos == n)
		pivot = pos - 1;
	else 
		pivot = pos;

	lptr = p[pivot];
	rptr = p[pivot + 1];
	lptr->keys[lptr->keys_num] = key_arr[pivot];
	lptr->children[lptr->keys_num + 1] = rptr->children[0];

	for (i = 0; i < rptr->keys_num; i++) {
		lptr->keys[lptr->keys_num + 1 + i] = rptr->keys[i];
		lptr->children[lptr->keys_num + 2 + i] = rptr->children[i + 1];
	}

	lptr->keys_num = lptr->keys_num + rptr->keys_num + 1;
	free(rptr);

	for (i = pos + 1; i < n; i++) {
		key_arr[i - 1] = key_arr[i];
		p[i] = p[i + 1];
	}

	return --node->keys_num >= (node == root ? 1 : MIN) ? SUCCESS : LESS_KEYS;
}


void deleting_node(int key) {
	Node* uproot;
	Key_status value;
	value = deleting(root, key);

	if (value == LESS_KEYS) {
		uproot = root;
		root = root->children[0];
		free(uproot);
	}
}


void split(Node* upnode, int index) {
	Node* rptr = allocate();
	Node* lptr = upnode->children[index];
	rptr->keys_num = MIN;

	for (int i = 0; i < MIN; i++) 
		rptr->keys[i] = lptr->keys[i + Tr];
	
	if (lptr->children[0] != NULL) 
		for (int i = 0; i < Tr; i++)
			rptr->children[i] = lptr->children[i + Tr];
	
	lptr->keys_num = MIN;

	for (int i = upnode->keys_num; i >= index; i--) 
		upnode->children[i + 1] = upnode->children[i];
	
	upnode->children[index + 1] = rptr;

	for (int i = upnode->keys_num - 1; i >= index; i--) 
		upnode->keys[i + 1] = upnode->keys[i];
	
	upnode->keys[index] = lptr->keys[Tr - 1];
	upnode->keys_num++;
}


void not_full_check(Node* node, int data) {
	int len = node->keys_num - 1;

	if (node->children[0] == NULL) {
		while (len >= 0 && data < node->keys[len]) {
			node->keys[len + 1] = node->keys[len];
			len--;
		}

		node->keys[len + 1] = data;
		node->keys_num++;
	}
	else {
		while (len >= 0 && data < node->keys[len]) 
			len--;
		
		len++;

		if (node->children[len]->keys_num == MAX) {
			split(node, len);
			if (data > node->keys[len]) {
				len++;
			}
		}

		not_full_check(node->children[len], data);
	}

}


void inserting_node(int data) {
	if (root == NULL) {
		root = allocate();
		root->keys[0] = data;
		root->keys_num = 1;
	}
	else 
		if (root->keys_num == MAX) {
			Node* old_root = root;
			Node* new_root_node = allocate();
			root = new_root_node;
			new_root_node->children[0] = old_root;
			split(new_root_node, 0);
			not_full_check(new_root_node, data);
		}
		else 
			not_full_check(root, data);
}


int searching(int data) {
	Node* cur = root;
	int child_index = 0;

	while (cur != NULL) {
		for (int i = 0; i < cur->keys_num; i++) 
			if (data == cur->keys[i]) {
				return TRUE;
			
			if (data < cur->keys[i]) {
				child_index = i;
				break;
			}
			else 
				child_index = i + 1;

		}

		cur = cur->children[child_index];
	}

	return 0;
}


void set_position(int x, int y) {
	COORD c;
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}


int calculate_width(Node* node) {
	int width = 0;

	for (int i = 0; i < node->keys_num; i++) {
		int x = node->keys[i];

		while (x != 0) {
			x /= 10;
			width++;
		}
	}

	return width;
}

int x = 1;

void printing(Node* node, int y, int width) {
	if (node == NULL) 
		return;
	
	printing(node->children[0], y + 2, width);

	set_position(x, y);
	printf("( ");

	for (int i = 0; i < node->keys_num; i++) 
		printf("%d ", node->keys[i]);
	
	printf(")");

	for (int i = 1; i <= node->keys_num; i++) {
		x += width + 4;
		printing(node->children[i], y + 2, width);
	}
}


void print_tree(int y) {
	x = 1;
	int width = calculate_width(root);
	printing(root, y, width);
}