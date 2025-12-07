#include <stdio.h>
#include <assert.h>

/*
A rectangular chessboard consists of 'num_rows' rows and 'num_cols'
columns. Place 'num_queens' queens on the chessboard so that no
two queens share the same row, column, or diagonal. Return the
total number of different solutions.

We gurantee num_rows, num_cols, num_queens <= 10.
*/
int place_queens(int num_rows, int num_cols, int num_queens) {
  
  return 0;// change 0 to your answer
}

void TestCase() {
  // Test Case : 1
  assert(place_queens(1,1,1) == 1);
  printf("Passed TestCase1\n");
  
  // Test Case : 2
  assert(place_queens(2,2,2) == 0);
  printf("Passed TestCase2\n");
  
  // Test Case : 3
  assert(place_queens(3,3,3) == 0);
  printf("Passed TestCase3\n");
  
  // Test Case : 4
  assert(place_queens(4,4,4) == 2);
  printf("Passed TestCase4\n");
  
  // Test Case : 5
  assert(place_queens(5,5,5) == 10);
  printf("Passed TestCase5\n");

  // Test Case : 6
  assert(place_queens(6,6,6) == 4);
  printf("Passed TestCase6\n");

  // Test Case : 7
  assert(place_queens(7,7,7) == 40);
  printf("Passed TestCase7\n");

  // Test Case : 8
  assert(place_queens(8,8,8) == 92);
  printf("Passed TestCase8\n");

  // Test Case : 9
  assert(place_queens(9,9,9) == 352);
  printf("Passed TestCase9\n");

  // Test Case : 10
  assert(place_queens(10,10,10) == 724);
  printf("Passed TestCase10\n");
  
  // Test Case : 11
  assert(place_queens(3,8,3) == 140);
  printf("Passed TestCase11\n");
  
  // Test Case : 12
  assert(place_queens(4,5,4) == 12);
  printf("Passed TestCase12\n");
  
  // Test Case : 13
  assert(place_queens(5,9,4) == 3942);
  printf("Passed TestCase13\n");

  // Test Case : 14
  assert(place_queens(5,10,5) == 3916);
  printf("Passed TestCase14\n");
  
  printf("All tests passed!\n");
}

int main() {
  TestCase();
  return 0;
}