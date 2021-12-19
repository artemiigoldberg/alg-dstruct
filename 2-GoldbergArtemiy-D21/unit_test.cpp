#include <gtest/gtest.h>

extern "C" {
	#include "check.h"
	#include <string.h>
}

#define TEST_CHECK_LINE 100

TEST(simple_test, test1) {
	FILE* Fp = fopen("example_input.txt", "w");

	fprintf(Fp, "3\n"\
		"2 3\n"\
		"1 3\n"\
		"1 2\n");

	fclose(Fp);
	Fp = fopen("example_input.txt", "r");

	graph_from_file(Fp);
	solve();
	
	fclose(Fp);
	
	Fp = fopen("example_output.txt", "w");
	print_ans(Fp);
	
	fclose(Fp);
	
	Fp = fopen("example_output.txt", "r");
	
	char line[TEST_CHECK_LINE] = {0};
	fgets(line, TEST_CHECK_LINE, Fp);
	
	EXPECT_TRUE(strcmp(line, "1 2 3 ") == 0);
}

TEST(border_test, zero_vertexses_without_value) {
	FILE* Fp = fopen("example_input.txt", "w");

	fprintf(Fp, "0\n");

	fclose(Fp);
	Fp = fopen("example_input.txt", "r");

	graph_from_file(Fp);
	solve();
	
	fclose(Fp);
	
	Fp = fopen("example_output.txt", "w");
	print_ans(Fp);
	
	fclose(Fp);
	
	Fp = fopen("example_output.txt", "r");
	
	char line[TEST_CHECK_LINE] = {0};
	fgets(line, TEST_CHECK_LINE, Fp);
	
	EXPECT_TRUE(strcmp(line, "0") == 0);
}

TEST(border_test, zero_vertexses_with_value) {
	FILE* Fp = fopen("example_input.txt", "w");

	fprintf(Fp, "0\n"\
		"1 2\n");

	fclose(Fp);
	Fp = fopen("example_input.txt", "r");

	EXPECT_EXIT(graph_from_file(Fp),::testing::KilledBySignal(SIGSEGV),".*");
}

TEST(usages_cases, single_vertexses_without_value) {
	FILE* Fp = fopen("example_input.txt", "w");

	fprintf(Fp, "1\n");

	fclose(Fp);
	Fp = fopen("example_input.txt", "r");

	graph_from_file(Fp);
	solve();
	
	fclose(Fp);
	
	Fp = fopen("example_output.txt", "w");
	print_ans(Fp);
	
	fclose(Fp);
	
	Fp = fopen("example_output.txt", "r");
	
	char line[TEST_CHECK_LINE] = {0};
	fgets(line, TEST_CHECK_LINE, Fp);
	
	EXPECT_TRUE(strcmp(line, "1 ") == 0);
}

TEST(usages_cases, single_vertexses_with_value) {
	FILE* Fp = fopen("example_input.txt", "w");

	fprintf(Fp, "1\n"\
		"1 2\n");

	fclose(Fp);
	Fp = fopen("example_input.txt", "r");

	EXPECT_EXIT(graph_from_file(Fp),::testing::KilledBySignal(SIGSEGV),".*");
}

TEST(usages_cases, two_vertexses_without_value) {
	FILE* Fp = fopen("example_input.txt", "w");

	fprintf(Fp, "2\n");

	fclose(Fp);
	Fp = fopen("example_input.txt", "r");

	graph_from_file(Fp);
	solve();
	
	fclose(Fp);
	
	Fp = fopen("example_output.txt", "w");
	print_ans(Fp);
	
	fclose(Fp);
	
	Fp = fopen("example_output.txt", "r");
	
	char line[TEST_CHECK_LINE] = {0};
	fgets(line, TEST_CHECK_LINE, Fp);
	
	EXPECT_TRUE(strcmp(line, "1 1 ") == 0);
}

TEST(usages_cases, two_vertexses_with_value) {
	FILE* Fp = fopen("example_input.txt", "w");

	fprintf(Fp, "2\n"
		"1 2\n");

	fclose(Fp);
	Fp = fopen("example_input.txt", "r");

	graph_from_file(Fp);
	solve();
	
	fclose(Fp);
	
	Fp = fopen("example_output.txt", "w");
	print_ans(Fp);
	
	fclose(Fp);
	
	Fp = fopen("example_output.txt", "r");
	
	char line[TEST_CHECK_LINE] = {0};
	fgets(line, TEST_CHECK_LINE, Fp);
	
	EXPECT_TRUE(strcmp(line, "1 2 ") == 0);
}

TEST(usages_cases, three_vertexses_without_value) {
	FILE* Fp = fopen("example_input.txt", "w");

	fprintf(Fp, "3\n");

	fclose(Fp);
	Fp = fopen("example_input.txt", "r");

	graph_from_file(Fp);
	solve();
	
	fclose(Fp);
	
	Fp = fopen("example_output.txt", "w");
	print_ans(Fp);
	
	fclose(Fp);
	
	Fp = fopen("example_output.txt", "r");
	
	char line[TEST_CHECK_LINE] = {0};
	fgets(line, TEST_CHECK_LINE, Fp);
	
	EXPECT_TRUE(strcmp(line, "1 1 1 ") == 0);
}

TEST(usages_cases, three_vertexses_with_one_value) {
	FILE* Fp = fopen("example_input.txt", "w");

	fprintf(Fp, "3\n"
		"1 2\n");

	fclose(Fp);
	Fp = fopen("example_input.txt", "r");

	graph_from_file(Fp);
	solve();
	
	fclose(Fp);
	
	Fp = fopen("example_output.txt", "w");
	print_ans(Fp);
	
	fclose(Fp);
	
	Fp = fopen("example_output.txt", "r");
	
	char line[TEST_CHECK_LINE] = {0};
	fgets(line, TEST_CHECK_LINE, Fp);
	
	EXPECT_TRUE(strcmp(line, "1 1 1 ") == 0);
}

TEST(usages_cases, three_vertexses_with_two_value) {
	FILE* Fp = fopen("example_input.txt", "w");

	fprintf(Fp, "3\n"
		"1 2\n"
		"2 3\n");

	fclose(Fp);
	Fp = fopen("example_input.txt", "r");

	graph_from_file(Fp);
	solve();
	
	fclose(Fp);
	
	Fp = fopen("example_output.txt", "w");
	print_ans(Fp);
	
	fclose(Fp);
	
	Fp = fopen("example_output.txt", "r");
	
	char line[TEST_CHECK_LINE] = {0};
	fgets(line, TEST_CHECK_LINE, Fp);
	
	EXPECT_TRUE(strcmp(line, "1 2 3 ") == 0);
}
