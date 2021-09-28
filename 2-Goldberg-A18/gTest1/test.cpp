#include "gtest/gtest.h"

extern "C" {
#include "node.h"
}

TEST(push_test, nullptr_list__err1) {
	int result = push(NULL, "test");

	EXPECT_TRUE(result == 1);
}

TEST(push_test, list_nullptr__err1) {
	struct Node* list = NULL;
	int result = push(&list, "test");

	EXPECT_TRUE(result == 1);
}

TEST(push_test, str_nullptr__err1) {
	struct Node* list = (struct Node*)malloc(sizeof(struct Node));
	
	if (list == NULL) {
		return;
	}

	list->data = (char*)malloc(sizeof("test"));
	
	if (list->data == NULL){
		return;
	}

	strcpy(list->data, "test");
	list->next = NULL;
	int result = push(&list, NULL);

	EXPECT_TRUE(result == 1);
}

TEST(push_test, correct_list__new_el) {
	struct Node* list = (struct Node*)malloc(sizeof(struct Node));
	
	if (list == NULL){
		return;
	}

	list->data = (char*)malloc(sizeof("test"));
	
	if (list->data == NULL) {
		return;
	}

	strcpy(list->data, "test");
	list->next = NULL;
	int result = push(&list, "new");
	
	EXPECT_TRUE(result == 0);
	EXPECT_TRUE(strcmp(list->data, "new") == 0);
	EXPECT_TRUE(strcmp(list->next->data, "test") == 0);
}

TEST(print_list_test, list_nullptr__err1) {
	int result = print_list(NULL);
	
	EXPECT_TRUE(result == 1);
}

TEST(print_list_test, correct_list__fine_result) {
	struct Node list = { "test", NULL };
	int result = print_list(&list);
	
	EXPECT_TRUE(result == 0);
}

TEST(front_back_split_test, list_nullptr__err1) {
	struct Node* front = (struct Node*)malloc(sizeof(struct Node));
	struct Node* back = (struct Node*)malloc(sizeof(struct Node));
	
	if (front == NULL || back == NULL) {
		return;
	}

	int result = front_back_split(NULL, &front, &back);
	
	EXPECT_TRUE(result == 1);
}

TEST(front_back_split_test, nullptr_front__err1) {
	struct Node list = { "test", NULL };
	struct Node* back = (struct Node*)malloc(sizeof(struct Node));
	
	if (back == NULL) {
		return;
	}

	int result = front_back_split(&list, NULL, &back);
	
	EXPECT_TRUE(result == 1);
}

TEST(front_back_split_test, nullptr_back__err1) {
	struct Node list = { "test", NULL };
	struct Node* front = (struct Node*)malloc(sizeof(struct Node));
	
	if (front == NULL) {
		return;
	}

	int result = front_back_split(&list, &front, NULL);
	
	EXPECT_TRUE(result == 1);
}

TEST(front_back_split_test, one_el_list__head_n_nullptr) {
	struct Node list = { "test", NULL };
	struct Node* front = (struct Node*)malloc(sizeof(struct Node));
	struct Node* back = (struct Node*)malloc(sizeof(struct Node));
	
	if (front == NULL || back == NULL) {
		return;
	}

	int result = front_back_split(&list, &front, &back);
	
	EXPECT_TRUE(front == &list && back == NULL);
}

TEST(front_back_split_test, even_len_list__half_split) {
	struct Node node3 = { "test_node_3", NULL };
	struct Node node2 = { "test_node_2", &node3 };
	struct Node node1 = { "test_node_1", &node2 };
	struct Node list = { "test_list", &node1 };
	struct Node* front = (struct Node*)malloc(sizeof(struct Node));
	struct Node* back = (struct Node*)malloc(sizeof(struct Node));
	
	if (front == NULL || back == NULL)	{
		return;
	}

	int result = front_back_split(&list, &front, &back);
	
	EXPECT_TRUE(front == &list && back == &node2);
}

TEST(front_back_split_test, odd_len_list__half_split) {
	struct Node node4 = { "test_node_4", NULL };
	struct Node node3 = { "test_node_3", &node4 };
	struct Node node2 = { "test_node_2", &node3 };
	struct Node node1 = { "test_node_1", &node2 };
	struct Node list = { "test_list", &node1 };
	struct Node* front = (struct Node*)malloc(sizeof(struct Node));
	struct Node* back = (struct Node*)malloc(sizeof(struct Node));
	
	if (front == NULL || back == NULL) {
		return;
	}

	int result = front_back_split(&list, &front, &back);
	
	EXPECT_TRUE(front == &list && back == &node3);
}

TEST(merge_splited_test, both_args_nullptr__nullptr) {
	struct Node* result = merge_splited(NULL, NULL);

	EXPECT_TRUE(result == NULL);
}

TEST(merge_splited_test, first_arg_nullptr__second_arg) {
	struct Node* first = NULL;
	struct Node second = { "test", NULL };
	struct Node* result = merge_splited(first, &second);

	EXPECT_TRUE(result == &second);
}

TEST(merge_splited_test, second_arg_nullptr__first_arg) {
	struct Node first = { "test", NULL };
	struct Node* second = NULL;
	struct Node* result = merge_splited(&first, second);

	EXPECT_TRUE(result == &first);
}

TEST(merge_splited_test, two_correct_els__two_els_sorted_list) {
	struct Node first = { "testB", NULL };
	struct Node second = { "testA", NULL };
	struct Node* result = merge_splited(&first, &second);

	EXPECT_TRUE(result == &second && result->next == &first);
}

TEST(merge_sort_test, list_nullptr__err1) {
	int result = merge_sort(NULL);

	EXPECT_TRUE(result == 1);
}

TEST(merge_sort_test, correct_list__sort_list) {
	struct Node* list = (struct Node*)malloc(sizeof(struct Node));
	struct Node* node1 = (struct Node*)malloc(sizeof(struct Node));
	struct Node* node2 = (struct Node*)malloc(sizeof(struct Node));
	struct Node* node3 = (struct Node*)malloc(sizeof(struct Node));
	struct Node* node4 = (struct Node*)malloc(sizeof(struct Node));
	
	if (list == NULL || node1 == NULL || node2 == NULL || node3 == NULL || node4 == NULL) {
		return;
	}

	list->data = (char*)malloc(sizeof("testB"));
	node1->data = (char*)malloc(sizeof("testO"));
	node2->data = (char*)malloc(sizeof("testZ"));
	node3->data = (char*)malloc(sizeof("testC"));
	node4->data = (char*)malloc(sizeof("testG"));
	
	if (list->data == NULL || node1->data == NULL || node2->data == NULL || node3->data == NULL || node4->data == NULL) {
		return;
	}

	strcpy(list->data, "testB");
	strcpy(node1->data, "testO");
	strcpy(node2->data, "testZ");
	strcpy(node3->data, "testC");
	strcpy(node4->data, "testG");

	list->next = node1;
	node1->next = node2;
	node2->next = node3;
	node3->next = node4;
	node4->next = NULL;

	merge_sort(&list);

	EXPECT_TRUE(strcmp(list->data, "testB") == 0);
	EXPECT_TRUE(strcmp(list->next->data, "testC") == 0);
	EXPECT_TRUE(strcmp(list->next->next->data, "testG") == 0);
	EXPECT_TRUE(strcmp(list->next->next->next->data, "testO") == 0);
	EXPECT_TRUE(strcmp(list->next->next->next->next->data, "testZ") == 0);
}
