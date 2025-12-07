#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// Dynamically allocate an int array of length n,
// initialize every element to `value`, and
// return a pointer to the allocated array.
int* create_and_fill_array(int n, int value) {
  // Write your code here.
  // Make sure the pointer you return is NULL or is valid.
}

void TestCreateAndFillArrayCase1(int* (*create_and_fill_array)(int, int)) {
  int n = 5;
  int value = 3;
  int *arr = create_and_fill_array(n, value);
  assert(arr != NULL);
  for (int i = 0; i < n; i++) {
    assert(arr[i] == value);
  }
  free(arr);
  printf("Passed %s\n", __func__);
}

void TestcreateAndFillArrayCase2(int* (*create_and_fill_array)(int, int)) {
  int n = 1;
  int value = 0;
  int* arr = create_and_fill_array(n, value);
  assert(arr != NULL);
  assert(arr[0] == value);
  free(arr);
  printf("Passed %s\n", __func__);
}

void TestCreateAndFillArrayCase3(int* (*create_and_fill_array)(int, int)) {
  int n = 3;
  int value = -1;
  int* arr = create_and_fill_array(n, value);
  assert(arr != NULL);
  for (int i = 0; i < n; i++) {
    assert(arr[i] == value);
  }
  free(arr);
  printf("Passed %s\n", __func__);
}

void TestCreateAndFillArrayCase4(int* (*create_and_fill_array)(int, int)) {
  int n = 0;
  int value = 10;
  int* arr = create_and_fill_array(n, value);
  assert(arr == NULL);
  printf("Passed %s\n", __func__);
}

void TestCreateAndFillArrayCase5(int* (*create_and_fill_array)(int, int)) {
  int n = -5;
  int value = -5;
  int* arr = create_and_fill_array(n, value);
  assert(arr == NULL);
  printf("Passed %s\n", __func__);
}

int main() {
  TestCreateAndFillArrayCase1(create_and_fill_array);
  TestcreateAndFillArrayCase2(create_and_fill_array);
  TestCreateAndFillArrayCase3(create_and_fill_array);
  TestCreateAndFillArrayCase4(create_and_fill_array);
  TestCreateAndFillArrayCase5(create_and_fill_array);
  printf("\nAll tests passed!\n");
  return 0;
}
