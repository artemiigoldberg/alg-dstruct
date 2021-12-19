#include <stdlib.h>
#include "check.h"

#define TRUE 1
#define FALSE 0

int vertex_number, *mark, **graph, *path, u = 0, v = 0, j = 1; //u, v - verteces of the graph
char f = FALSE, check_false;

static char __check(int vertex) {
	mark[vertex] = TRUE;
	path[j - 1] = vertex;

	if (j == vertex_number)
		return TRUE;

	for (int i = 0; i < vertex_number; i++) {
		if (graph[vertex][i] && !mark[i]) {
			j++;
			check_false = __check(i);
		}

		if (check_false == FALSE) {
			if (i == vertex_number - 1) {
				j--;
				mark[vertex] = 0;
				return FALSE;
			}

		}
		else
			return TRUE;
	}

	return FALSE;
}

void solve(){
	int vertex_count = 0;

	while (vertex_count < vertex_number && f == FALSE) {
		if (__check(vertex_count)) {
			f = TRUE;
			break;
		}
		else 
			for (int i = 0; i < vertex_number; i++) 
				mark[i] = 0;

		j = 1;
		vertex_count++;
	}
}


void graph_from_file(FILE* Fp) {
	fscanf(Fp, "%d", &vertex_number);
	
	f = FALSE;
	
	mark = (int*)calloc(vertex_number, sizeof(int));
	graph = (int**)calloc(vertex_number, sizeof(int*));
	path = (int*)calloc(vertex_number, sizeof(int));
	
	for (int i = 0; i < vertex_number; i++)
		graph[i] = (int*)calloc(vertex_number, sizeof(int));
	
	while (fscanf(Fp, "%d %d", &u, &v) == 2)
		if (Fp == stdin && u == 0)
			break;
		else
			graph[u - 1][v - 1] = graph[v - 1][u - 1] = TRUE;
}

void stress_test(){
	vertex_number = TEST_VERTEX_NUMBER;
	
	mark = (int*)calloc(vertex_number, sizeof(int));
	graph = (int**)calloc(vertex_number, sizeof(int*));
	path = (int*)calloc(vertex_number, sizeof(int));
	
	for (int i = 0; i < vertex_number; i++)
		graph[i] = (int*)calloc(vertex_number, sizeof(int));
	
	for (int i = 0; i < TEST_VERTEX_NUMBER; i++)
		for (int j = i + 1; j < TEST_VERTEX_NUMBER; j++)
			if (rand() % 4 <= 3)
				graph[i][j] = graph[j][i] = 1;
}

void print_ans(FILE* Fp){
	if (f == TRUE && vertex_number != 0)
		for (int i = 0; i < vertex_number; i++)
			fprintf(Fp, "%d ", path[i] + 1);
	else
		fprintf(Fp, "%d", 0);
}
