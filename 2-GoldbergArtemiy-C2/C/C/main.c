/*
	Intel(R) Core(TM) i5-6400 CPU @ 2.70GHz 
	HDD SATA 6 Gb/s 500 GB
	RAM: 16 GB dual-channel 1200 MHz

	596.07 MB for graph storage and DFS execution
	601.36 MB - total memory for whole programm
	8.2 sec - programm execution time
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <time.h>
#include "Stack.h"
#define TRUE 1
#define FALSE 0
#define TEST_VERTEX_NUMBER 25000

int vertex_number, *mark, u = 0, v = 0; //u, v - verteces of the graph
char** graph;
stack_t* stack;

void dfs(int vertex) {
	unsigned long long start = clock();
	mark[vertex] = TRUE;
	fprintf(stdout, "%d ", vertex);

	for (int i = 0; i < vertex_number; i++) {
		if (graph[vertex][i] && !mark[i]) {
			push(stack, i);
			vertex = i;
			fprintf(stdout, "%d ", vertex);
			mark[vertex] = TRUE;
			i = 0;
		}

		if (i == vertex_number - 1) {
			vertex = pop(stack);

			if (vertex == 0) {
				unsigned long long end = clock();
				fprintf(stdout, "%f", (double)(end - start) / CLK_TCK);
				return;
			}

			i = 0;
		}

	}
}

void stress_test() {
	srand(time(NULL));
	stack = (stack_t*)malloc(sizeof(stack_t));
	stack->head = NULL;
	char** matrix = (char**)calloc(TEST_VERTEX_NUMBER, sizeof(char*));

	if (matrix == NULL)
		return 0;

	for (int i = 0; i < TEST_VERTEX_NUMBER; i++) {
		matrix[i] = (char*)calloc(TEST_VERTEX_NUMBER, sizeof(char));

		if (matrix[i] == NULL) 
			return 0;
	}

	for (int i = 0; i < TEST_VERTEX_NUMBER; i++)
		for (int j = i + 1; j < TEST_VERTEX_NUMBER; j++)
			matrix[i][j] = matrix[j][i] = rand() % 2;

	FILE* Fp = fopen("stress_test.txt", "w");

	fprintf(Fp, "%d\n", TEST_VERTEX_NUMBER);

	for (int i = 0; i < TEST_VERTEX_NUMBER; i++)
		for (int j = i + 1; j < TEST_VERTEX_NUMBER; j++)
			if (matrix[i][j] == TRUE)
				fprintf(Fp, "%d %d\n", i, j);

	fclose(Fp);

	for (int i = 0; i < TEST_VERTEX_NUMBER; i++)
		free(matrix[i]);

	free(matrix);

	Fp = fopen("stress_test.txt", "r");

	fscanf(Fp, "%d", &vertex_number);
	mark = (int*)calloc(vertex_number, sizeof(int));
	graph = (char**)calloc(vertex_number, sizeof(char*));

	for (int i = 0; i < vertex_number; i++)
		graph[i] = (char*)calloc(vertex_number, sizeof(char));

	while (fscanf(Fp, "%d %d", &u, &v) != EOF)
		graph[u][v] = graph[v][u] = TRUE;

	push(stack, 0);
	dfs(0);

	fclose(Fp);
}

int main() {
	stress_test();

	getchar();
	return 0;
}