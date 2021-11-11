#pragma once

struct list_t {
	struct list_t* next;
	int value;
};

typedef struct {
	struct list_t* head;
} stack_t;

typedef struct list_t list;

int pop(stack_t* stack);
void push(stack_t* stack, int value);

