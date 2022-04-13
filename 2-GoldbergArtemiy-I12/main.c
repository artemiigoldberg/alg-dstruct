#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include "tree.h"


int main() {
	char command;
	int value;

	while (scanf("%c", &command) >= 1) {
		if (command != 'p' && command != 'q') 
			scanf("%d", &value);
		
		switch (command) {
		case 'a':
			inserting_node(value);
			break;
		case 'r':
			deleting_node(value);
			break;
		case 'f':
			if (searching(value))
				puts("yes");
			else
				puts("no");
			break;
		case 'p':
			system("cls");
			print_tree(0);
			break;
		case 'q':
			return 0;
			break;
		}
	}

	return 0;
}