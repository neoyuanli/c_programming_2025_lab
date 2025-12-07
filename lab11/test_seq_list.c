#include "seq_list.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void array_to_list(const int* arr, int arr_len, List* ptr_list) {
    list_init(ptr_list, arr_len);
    for (int i = 0; i < arr_len; i++) {
        ptr_list->list[i] = arr[i];
    }
    ptr_list->len = arr_len;
}

//-- Test Cases for list_init --//
void test_list_init_case1(){
    List my_list;
    int ret = list_init(&my_list, 5);
    assert(ret == 0);
    assert(my_list.max_len == 5);
    assert(my_list.len == 0);
    assert(my_list.list != NULL);
    list_free(&my_list);
}

void test_list_init_case2(){
    List my_list;
    int ret = list_init(&my_list, 0);
    assert(ret != 0);
    assert(my_list.list == NULL);
    assert(my_list.len == 0);
    assert(my_list.max_len == 0);
    list_free(&my_list);
}

// -- Test Cases for list_free -- //
void test_list_free_case1(){
    List my_list;
    list_init(&my_list, 5);
    list_free(&my_list);
    assert(my_list.list == NULL);
    assert(my_list.len == 0);
    assert(my_list.max_len == 0);
}

void test_list_free_case2(){
    List my_list;
    list_init(&my_list, 0);
    list_free(&my_list);
    assert(my_list.list == NULL);
    assert(my_list.len == 0);
    assert(my_list.max_len == 0);
}

// -- Test Cases for list_insert_element -- //
void test_list_insert_case1(){
    List my_list;
    list_init(&my_list, 2);
    int ret = list_insert_element(&my_list, 0, 10);
    assert(ret == 0);
    assert(my_list.len == 1);
    assert(my_list.max_len >= 1);
    assert(my_list.list[0] == 10);
    list_free(&my_list);
}

void test_list_insert_case2(){
    List my_list;
    list_init(&my_list, 2);
    list_insert_element(&my_list, 0, 10);
    list_insert_element(&my_list, 1, 20);
    int ret = list_insert_element(&my_list, 0, 15); // This should trigger a resize
    assert(ret == 0);
    assert(my_list.len == 3);
    assert(my_list.max_len >= 3);
    assert(my_list.list[0] == 15);
    assert(my_list.list[1] == 10);
    assert(my_list.list[2] == 20);
    list_free(&my_list);
}
//invalid index tests
void test_list_insert_case3(){
    List my_list;
    list_init(&my_list, 2);
    int ret = list_insert_element(&my_list, -1, 10); // Invalid index
    assert(ret != 0);
    ret = list_insert_element(&my_list, 3, 10); // Invalid index
    assert(ret != 0);
    list_free(&my_list);
}
//performance test for large number of insertions
void test_list_insert_case4(){
    List my_list;
    list_init(&my_list, 1);
    const int N = 100000000;
    for(int i = 0; i < N; i++){
        int ret = list_insert_element(&my_list, i, i);
        assert(ret == 0);
    }
    assert(my_list.len == N);
    assert(my_list.max_len >= N);
    for(int i = 0; i < N; i++){
        assert(my_list.list[i] == i);
    }
    list_free(&my_list);
}

//-- Test Cases for list_append_element -- //
void test_list_append_case1(){
    List my_list;
    list_init(&my_list, 2);
    int ret = list_append_element(&my_list, 10);
    assert(ret == 0);
    assert(my_list.len == 1);
    assert(my_list.max_len >= 1);
    assert(my_list.list[0] == 10);
    list_free(&my_list);
}

void test_list_append_case2(){
    List my_list;
    list_init(&my_list, 2);
    list_append_element(&my_list, 10);
    list_append_element(&my_list, 20);
    int ret = list_append_element(&my_list, 30); // This should trigger a resize
    assert(ret == 0);
    assert(my_list.len == 3);
    assert(my_list.max_len >= 3);
    assert(my_list.list[0] == 10);
    assert(my_list.list[1] == 20);
    assert(my_list.list[2] == 30);
    list_free(&my_list);
}

//performance test for large number of appends
void test_list_append_case3(){
    List my_list;
    list_init(&my_list, 1);
    const int N = 110000000;
    for(int i = 0; i < N; i++){
        int ret = list_append_element(&my_list, i);
        assert(ret == 0);
    }
    assert(my_list.len == N);
    assert(my_list.max_len >= N);
    for(int i = 0; i < N; i++){
        assert(my_list.list[i] == i);
    }
    list_free(&my_list);
}

//--Test cases for list_delete_element--//
void test_list_delete_case1(){
    List my_list;
    array_to_list((int[]){10, 20, 30}, 3, &my_list);
    int ret = list_delete_element(&my_list, 1);
    assert(ret == 0);
    assert(my_list.len == 2);
    assert(my_list.list[0] == 10);
    assert(my_list.list[1] == 30);
    list_free(&my_list);
}

void test_list_delete_case2(){
    List my_list;
    array_to_list((int[]){10}, 1, &my_list);
    int ret = list_delete_element(&my_list, 0);
    assert(ret == 0);
    assert(my_list.len == 0);
    list_free(&my_list);
}

void test_list_delete_case3(){
    List my_list;
    array_to_list((int[]){10, 20}, 2, &my_list);
    int ret = list_delete_element(&my_list, -1); // Invalid index
    assert(ret != 0);
    ret = list_delete_element(&my_list, 2); // Invalid index
    assert(ret != 0);
    list_free(&my_list);
}

// --Test cases for list_search_element--//
void test_list_search_case1(){
    List my_list;
    array_to_list((int[]){10, 20, 30}, 3, &my_list);
    int idx = list_search_element(&my_list, 20);
    assert(idx == 1);
    assert(my_list.list[idx] == 20);
    idx = list_search_element(&my_list, 40);
    assert(idx == -1);
    list_free(&my_list);
}

//-- Test cases for list_binary_search -- //
void test_list_binary_search_case1(){
    List my_list;
    array_to_list((int[]){10, 20, 30}, 3, &my_list);
    int idx = list_binary_search(&my_list, 20);
    assert(idx == 1);
    assert(my_list.list[idx] == 20);
    idx = list_binary_search(&my_list, 40);
    assert(idx == -1);
    list_free(&my_list);
}

void test_list_binary_search_case2(){
    List my_list;
    array_to_list((int[]){5, 15, 35, 67, 80}, 5, &my_list);
    int idx = list_binary_search(&my_list, 35);
    assert(idx == 2);
    assert(my_list.list[idx] == 35);
    idx = list_binary_search(&my_list, 80);
    assert(idx == 4);
    assert(my_list.list[idx] == 80);
    idx = list_binary_search(&my_list, 15);
    assert(idx == 1);
    assert(my_list.list[idx] == 15);
    idx = list_binary_search(&my_list, 100);
    assert(idx == -1);
    list_free(&my_list);
}

// --Test cases for list_concat--//
void test_list_concat_case1(){
    List list1, list2;
    array_to_list((int[]){10, 20}, 2, &list1);
    array_to_list((int[]){30, 40}, 2, &list2);
    int ret = list_concat(&list1, &list2);
    assert(ret == 0);
    assert(list1.len == 4);
    assert(list1.list[0] == 10);
    assert(list1.list[1] == 20);
    assert(list1.list[2] == 30);
    assert(list1.list[3] == 40);
    list_free(&list1);
    list_free(&list2);
}

void test_list_concat_case2(){
    List list1, list2;
    array_to_list((int[]){10, 20}, 2, &list1);
    array_to_list((int[]){30, 40, 50}, 3, &list2);
    int ret = list_concat(&list1, &list2); // This should trigger a resize
    assert(ret == 0);
    assert(list1.len == 5);
    assert(list1.list[0] == 10);
    assert(list1.list[1] == 20);
    assert(list1.list[2] == 30);
    assert(list1.list[3] == 40);
    assert(list1.list[4] == 50);
    list_free(&list1);
    list_free(&list2);
}

//--Test cases for list_fprint--//
void test_list_fprint_case1(){
    List my_list;
    array_to_list((int[]){10, 20, 30}, 3, &my_list);
    FILE *fp = fopen("test_output.txt", "w");
    list_fprint(fp, &my_list);
    fclose(fp);

    // Verify file content
    fp = fopen("test_output.txt", "r");
    char buffer[100];
    fgets(buffer, sizeof(buffer), fp);
    fclose(fp);
    assert(strstr(buffer, "10 20 30") != NULL);
    list_free(&my_list);
}

void test_list_fprint_case2(){
    List my_list;
    array_to_list((int[]){10, 30, 70, 40}, 4, &my_list);
    list_fprint(stdout, &my_list); // Print to console
    fflush(stdout); // Ensure output is printed immediately
    list_free(&my_list);
}

// -- Test cases for list_sort -- //
void test_list_sort_case1(){
    List my_list;
    array_to_list((int[]){30, 10, 20}, 3, &my_list);
    list_sort(&my_list);
    assert(my_list.list[0] == 10);
    assert(my_list.list[1] == 20);
    assert(my_list.list[2] == 30);
    list_free(&my_list);
}

void test_list_sort_case2(){
    List my_list;
    array_to_list((int[]){10, 20, 30, 10, 50}, 5, &my_list);
    list_sort(&my_list);
    assert(my_list.list[0] == 10);
    assert(my_list.list[1] == 10);
    assert(my_list.list[2] == 20);
    assert(my_list.list[3] == 30);
    assert(my_list.list[4] == 50);
    list_free(&my_list);
}

//--Test for list_init--
void test_list_init(){
    test_list_init_case1();
    test_list_init_case2();
}

//--Test for list_free--
void test_list_free(){
    test_list_free_case1();
    test_list_free_case2();
}

//--Test for list_insert_element--
void test_list_insert_element(){
    test_list_insert_case1();
    test_list_insert_case2();
    test_list_insert_case3();
    test_list_insert_case4();
}

//--Test for list_append_element--
void test_list_append_element(){
    test_list_append_case1();
    test_list_append_case2();
    test_list_append_case3();
}

//--Test for list_delete_element--
void test_list_delete_element(){
    test_list_delete_case1();
    test_list_delete_case2();
    test_list_delete_case3();
}

//--Test for list_search_element--
void test_list_search_element(){
    test_list_search_case1();
}

//--Test for list_binary_search--
void test_list_binary_search(){
    test_list_binary_search_case1();
    test_list_binary_search_case2();
}

//--Test for list_concat--
void test_list_concat(){
    test_list_concat_case1();
    test_list_concat_case2();
}

//--Test for list_fprint--
void test_list_fprint(){
    test_list_fprint_case1();
    test_list_fprint_case2();
}

//--Test for list_sort--
void test_list_sort(){
    test_list_sort_case1();
    test_list_sort_case2();
}

int main(void) {
    test_list_init();
    printf("Passed list_init tests\n");
    test_list_free();
    printf("Passed list_free tests\n");
    test_list_insert_element();
    printf("Passed list_insert_element tests\n");
    test_list_append_element();
    printf("Passed list_append_element tests\n");
    test_list_delete_element();
    printf("Passed list_delete_element tests\n");
    test_list_search_element();
    printf("Passed list_search_element tests\n");
    test_list_binary_search();
    printf("Passed list_binary_search tests\n");
    test_list_concat();
    printf("Passed list_concat tests\n");
    test_list_fprint();
    printf("Passed list_fprint tests\n");
    test_list_sort();
    printf("Passed list_sort tests\n");
    printf("All seq_list unit tests passed\n");
    return 0;
}
