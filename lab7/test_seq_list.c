#include "seq_list.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

void TestListInit() {
    // Only test list_init here
    int* list = list_init(5);
    assert(list != NULL);
    free(list);
    printf("Passed %s\n", __func__);
}

void TestListInsertElement() {
    // Build initial array directly without using other functions
    int* list = (int*)malloc(6 * sizeof(int)); // capacity 6
    // initial content: {10,20,30}, len=3
    list[0] = 10; list[1] = 20; list[2] = 30;
    int len = 3;

    // Insert at beginning
    list_insert_element(list, &len, 0, 5);
    assert(len == 4);
    assert(list[0] == 5 && list[1] == 10 && list[2] == 20 && list[3] == 30);

    // Insert in middle
    list_insert_element(list, &len, 2, 15); // expect {5,10,15,20,30}
    assert(len == 5);
    assert(list[2] == 15 && list[3] == 20);

    // Insert at end (index == len)
    list_insert_element(list, &len, len, 40);
    assert(len == 6);
    assert(list[5] == 40);

    free(list);
    printf("Passed %s\n", __func__);
}

void TestListAppendElement() {
    // Test append without using other functions
    int* list = (int*)malloc(5 * sizeof(int));
    int len = 0;

    list_append_element(list, &len, 100);
    assert(len == 1 && list[0] == 100);

    list_append_element(list, &len, 200);
    assert(len == 2 && list[1] == 200);

    list_append_element(list, &len, 300);
    assert(len == 3 && list[2] == 300);

    free(list);
    printf("Passed %s\n", __func__);
}

void TestListDeleteElement() {
    // Setup array directly
    int* list = (int*)malloc(5 * sizeof(int));
    list[0] = 10; list[1] = 20; list[2] = 30; list[3] = 40;
    int len = 4;

    // Delete from middle (index 1)
    list_delete_element(list, &len, 1);
    assert(len == 3);
    assert(list[0] == 10 && list[1] == 30 && list[2] == 40);

    // Delete from beginning (index 0)
    list_delete_element(list, &len, 0);
    assert(len == 2);
    assert(list[0] == 30 && list[1] == 40);

    // Delete from end (index len-1)
    list_delete_element(list, &len, len-1);
    assert(len == 1);
    assert(list[0] == 30);

    free(list);
    printf("Passed %s\n", __func__);
}

void TestListSearchElement() {
    // Setup array directly
    int arr[] = {10, 20, 30};
    int len = 3;

    assert(list_search_element(arr, len, 10) == 0);
    assert(list_search_element(arr, len, 20) == 1);
    assert(list_search_element(arr, len, 30) == 2);
    assert(list_search_element(arr, len, 99) == -1);

    printf("Passed %s\n", __func__);
}

void TestListBinarySearch() {
    // Setup sorted array directly
    int arr[] = {5, 10, 15, 20, 25};
    int len = 5;

    assert(list_binary_search(arr, len, 5) == 0);
    assert(list_binary_search(arr, len, 10) == 1);
    assert(list_binary_search(arr, len, 15) == 2);
    assert(list_binary_search(arr, len, 25) == 4);
    assert(list_binary_search(arr, len, 17) == -1);

    printf("Passed %s\n", __func__);
}

void TestListConcat() {
    // Prepare two arrays directly
    int* list1 = (int*)malloc(10 * sizeof(int));
    int* list2 = (int*)malloc(5 * sizeof(int));
    // list1 initially {1,2}
    list1[0] = 1; list1[1] = 2; int len1 = 2;
    // list2 {3,4}
    list2[0] = 3; list2[1] = 4; int len2 = 2;

    list_concat(list1, &len1, list2, len2);
    assert(len1 == 4);
    assert(list1[0] == 1 && list1[1] == 2 && list1[2] == 3 && list1[3] == 4);

    free(list1);
    free(list2);
    printf("Passed %s\n", __func__);
}

void TestListFprint() {
    // Setup array directly
    int* list = (int*)malloc(5 * sizeof(int));
    list[0] = 10; list[1] = 20; list[2] = 30; int len = 3;
    FILE* fp = tmpfile();
    char buffer[100];
    assert(fp != NULL);

    list_fprint(fp, list, len);
    rewind(fp);
    fgets(buffer, sizeof(buffer), fp);
    //assert(strcmp(buffer, "10 20 30\n") == 0);
    assert(strncmp(buffer, "10 20 30", 8) == 0);

    fclose(fp);
    free(list);
    printf("Passed %s\n", __func__);
}

void TestListSort() {
    // Test basic sort
    int a1[] = {3, 1, 4, 2};
    list_sort(a1, 4);
    assert(a1[0] == 1 && a1[1] == 2 && a1[2] == 3 && a1[3] == 4);

    // Test with duplicates
    int a2[] = {5, 2, 2, 1};
    list_sort(a2, 4);
    assert(a2[0] == 1 && a2[1] == 2 && a2[2] == 2 && a2[3] == 5);

    // Test empty (len = 0) should be safe
    int a3[1];
    list_sort(a3, 0);

    // Test single element
    int a4[] = {42};
    list_sort(a4, 1);
    assert(a4[0] == 42);

    printf("Passed %s\n", __func__);
}

int main() {
    TestListInit();
    TestListInsertElement();
    TestListAppendElement();
    TestListDeleteElement();
    TestListSearchElement();
    TestListBinarySearch();
    TestListConcat();
    TestListFprint();
    TestListSort();

    printf("\nAll tests passed!\n");
    return 0;
}