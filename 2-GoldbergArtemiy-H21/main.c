#define _CRT_SECURE_NO_WARNINGS
#include "Tree.h"
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
	char command;
	int value;

	RBTree* tree = NULL;
	init_tree(&tree);

	while (scanf("%c %d", &command, &value) >= 1) {
		switch (command) {
		case 'a':
			insert_node(&tree, value);
			break;
		case 'r':
			delete_node(&tree, value);
			break;
		case 'f':
			if (search_tree(tree, value))
				puts("yes");
			else
				puts("no");
			break;
		case 'p':
			print_tree(tree, 0);
			break;
		case 'q':
			return 0;
			break;
		}
	}

	return 0;
}

int cmain() {
	RBTree* tree = NULL;
	init_tree(&tree);
	insert_node(&tree, 10);
	insert_node(&tree, 10);
	delete_node(&tree, 10);
	print_tree(tree, 1);

	return 0;
}
