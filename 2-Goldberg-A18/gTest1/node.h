#pragma once

struct Node{
	char* data;
	struct Node* next;
};

int merge_sort(struct Node** list);
struct Node* merge_splited(struct Node* a, struct Node* b);
int front_back_split(struct Node* source, struct Node** front, struct Node** back);
int print_list(struct Node* list);
int push(struct Node** list, char* new_data);
