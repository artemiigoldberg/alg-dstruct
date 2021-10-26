#define _CRT_SECURE_NO_WARNINGS

#include "memallocator.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <windows.h>

#define MAX_ALLOC_SIZE 250
#define TEST_ITERATIONS 1000

int main() {
	FILE* file = fopen("memalloc_memfree.txt", "w");
	void* mem_pool = malloc((MAX_ALLOC_SIZE + 16) * TEST_ITERATIONS);
	meminit(mem_pool, (MAX_ALLOC_SIZE + 16) * TEST_ITERATIONS);
	double* results = (double*)malloc(TEST_ITERATIONS * sizeof(double));
	int* pointers = (int*)malloc(TEST_ITERATIONS * sizeof(int));
	long int start;
	
	LARGE_INTEGER frequency; 
	LARGE_INTEGER t1, t2; 
	double elapsedTime; 
	QueryPerformanceFrequency(&frequency);

	for (int test = 0; test < TEST_ITERATIONS; test++) {
		QueryPerformanceCounter(&t1);

		for (int iter = 0; iter < test; iter++)
			pointers[iter] = (int*)memalloc((int)rand() % MAX_ALLOC_SIZE);

		for (int iter = 0; iter < test; iter++)
			memfree(pointers[iter]);

		QueryPerformanceCounter(&t2);
		elapsedTime = (float)(t2.QuadPart - t1.QuadPart) / frequency.QuadPart;
		results[test] = elapsedTime;
	}

	for (int i = 0; i < TEST_ITERATIONS; i++)
		fprintf(file, "%lf;", results[i]);

	fclose(file);

	file = fopen("malloc_free.txt", "w");

	for (int test = 0; test < TEST_ITERATIONS; test++) {
		QueryPerformanceCounter(&t1);

		for (int iter = 0; iter < test; iter++) 
			pointers[iter] = (int*)malloc((int)rand() % MAX_ALLOC_SIZE);

		for (int iter = 0; iter < test; iter++)
			free(pointers[iter]);
		
		QueryPerformanceCounter(&t2); 
		elapsedTime = (float)(t2.QuadPart - t1.QuadPart) / frequency.QuadPart; 
		results[test] = elapsedTime;
	}

	for (int i = 0; i < TEST_ITERATIONS; i++) 
		fprintf(file, "%lf;", results[i]);
	
	fclose(file);

	free(results);
	free(pointers);
	free(mem_pool);

	return 0;
}
