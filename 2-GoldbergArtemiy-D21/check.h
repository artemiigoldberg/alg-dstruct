#pragma once
#include <stdio.h>

#define TEST_VERTEX_NUMBER 1000

void graph_from_file(FILE* Fp);
void solve();
void stress_test();
void print_ans(FILE* Fp);
