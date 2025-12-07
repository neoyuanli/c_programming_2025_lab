#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include<stdbool.h>

// Given n and an array of n-1 integers from the set {1, 2, ..., n},
// possibly missing multiple values,
// returns the smallest missing integer in the range [1, n].
// Returns -1 if the input is invalid 

int smallest_missing_element(int n, int* list) {

}

void TestCase1() {
  int n = 5;
  int list[4] = {1, 3, 4, 5};
  assert(smallest_missing_element(n, list) == 2);
  printf("Passed %s\n", __func__);
}

void TestCase2() {
  int n = 6;
  int list[6] = {4, 1, 3, 2, 5};
  assert(smallest_missing_element(n, list) == 6);
  printf("Passed %s\n", __func__);
}

void TestCase3() {
  // Multiple numbers are missing; the function should return the smallest missing one.
  int n = 10;
  int list[9] = {8, 4, 6, 2, 9, 10, 7, 6, 8}; // missing 1, 3, 5
  assert(smallest_missing_element(n, list) == 1);
  printf("Passed %s\n", __func__);
}


void TestCase4() {
  // Large input test to ensure it can handle high n without overflow.
  int n = 100000;          
  int missing = 54321;     // Randomly missing one
  int* list = malloc((n - 1) * sizeof(int));
  assert(list != NULL);

  int idx = 0;
  for (int i = 1; i <= n; i++) {
    if (i == missing) continue;
    list[idx++] = i;
  }

  
  for (int i = 0; i < n - 1; i++) {
    int j = rand() % (n - 1);
    int tmp = list[i];
    list[i] = list[j];
    list[j] = tmp;
  }

  assert(smallest_missing_element(n, list) == missing);
  printf("Passed %s (large n=%d)\n", __func__, n);

  free(list);
}

void TestCase5() {
  // Invalid input: n <= 0
  int n = 0;
  int list[1] = {1};
  assert(smallest_missing_element(n, list) == -1);
  printf("Passed %s\n", __func__);
}

int main() {
  TestCase1();
  TestCase2();
  TestCase3();
  TestCase4();
  TestCase5();
  printf("\nAll tests passed!\n");
  return 0;
}
