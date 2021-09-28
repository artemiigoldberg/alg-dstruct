#include <stdio.h>
#include <string.h>
#include "node.h"

int merge_sort(struct Node** list) {
	if (list == NULL)
	{
		return 1;
	}

	struct Node* head = *list;
	struct Node* a;
	struct Node* b;

	if ((head == NULL) || (head->next == NULL)) {
		return;
	}

	front_back_split(head, &a, &b);

	merge_sort(&a);
	merge_sort(&b);

	*list = merge_splited(a, b);
}

struct Node* merge_splited(struct Node* a, struct Node* b) {
	struct Node* result = NULL;

	if (a == NULL)
		return (b);
	else 
	    if (b == NULL)
		    return (a);

	if (strcmp(a->data, b->data) <= 0) {
		result = a;
		result->next = merge_splited(a->next, b);
	}
	else {
		result = b;
		result->next = merge_splited(a, b->next);
	}
	return (result);
}

int front_back_split(struct Node* list, struct Node** front, struct Node** back) {
	if (list == NULL || front == NULL || back == NULL)
	{
		return 1;
	}

	struct Node* fast;
	struct Node* slow;
	slow = list;
	fast = list->next;

	while (fast != NULL) {
		fast = fast->next;
		if (fast != NULL) {
			slow = slow->next;
			fast = fast->next;
		}
	}

	*front = list;
	*back = slow->next;
	slow->next = NULL;
}

int print_list(struct Node* list) {
	if (list == NULL)
	{
		return 1;
	}

	while (list != NULL) {
		printf("%s ", list->data);
		list = list->next;
	}
	printf("\n");

	return 0;
}

int push(struct Node** list, char* new_data) {
	if (list == NULL || (*list) == NULL || new_data == NULL)
	{
		return 1;
	}

	struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
	if (new_node == NULL)
		return 2;

	new_node->data = (char*)malloc(strlen(new_data) + 1);
	if (new_node->data == NULL)
		return 2;

	strcpy(new_node->data, new_data);

	new_node->next = (*list);
	(*list) = new_node;

	return 0;
}
