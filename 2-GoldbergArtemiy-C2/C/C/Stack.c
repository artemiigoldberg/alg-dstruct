#include "Stack.h"
#include <stdlib.h>

int pop(stack_t* stack) {
	list* node = stack->head;
	int value = node->value;
	stack->head = node->next;
	free(node);
	return value;
}


void push(stack_t* stack, int value) {
	list* node = (list*)malloc(sizeof(list));
	node->next = stack->head;
	node->value = value;
	stack->head = node;
	return;
}