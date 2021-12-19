#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
// #include <windows.h> 
// #include <psapi.h> 

#include "check.h"

#define TRUE 1
#define FALSE 0

#define DIV 1048576
#define WIDTH 7



int main() {
	//scanf("%d", &vertex_number);

	
	/*while (scanf("%d %d", &u, &v) == 2)
		graph[u - 1][v - 1] = graph[v - 1][u - 1] = TRUE;*/

	

	/*for (int i = 0; i < vertex_number; i++) {
		for (int k = 0; k < vertex_number; k++)
			printf("%d ", graph[i][k]);

		printf("\n");
	}*/

	graph_from_file(stdin);
	solve();
	print_ans(stdout);

// 	HINSTANCE hProcHandle = GetModuleHandle(NULL);  // get the current process handle
// 	PROCESS_MEMORY_COUNTERS_EX memory; // output will go here.
// 
// 	GetProcessMemoryInfo(hProcHandle, &memory, sizeof(memory));
// 	
// 	printf("\nMemory usage: %u MB", memory.PrivateUsage/DIV);
	return 0;
}
