#include <stdio.h>
#include <math.h>
#include <assert.h>

/* 
 * Given a positive integer n (n <= 10^8),
 * express n as a sum of k perfect squares:
 *     n = a1^2 + a2^2 + ... + ak^2,
 * where k <= 4.
 * The goal is to make k as small as possible.
 *
 * On return:
 *   - *k stores the minimal number of squares.
 *   - list[0..(*k - 1)] stores the corresponding integers a1, ..., ak.
 */
void sum_of_squares(int n, int* k, int* list) {
  
}

void TestCase1(){
  // 57988225 = 7615^2
  int k;
  int list[4] = {0};
  int n = 57988225;
  sum_of_squares(n, &k, list);
  assert(k == 1);
  assert(list[0] * list[0] == n);
  printf("Passed %s\n", __func__);
}

void TestCase2(){
  // 35721 = 189^2 
  int k;
  int list[4] = {0};
  int n = 35721;
  sum_of_squares(n, &k, list);
  assert(k == 1);
  assert(list[0] * list[0] == n);
  printf("Passed %s\n", __func__);
}

void TestCase3() {
  // 650000 = 700^2 + 400^2
  int k;
  int list[4] = {0};
  int n = 650000;
  sum_of_squares(n, &k, list);
  assert(k == 2);
  int sum = 0;
  for (int i = 0; i < k; ++i) sum += list[i] * list[i];
  assert(sum == n);
  printf("Passed %s\n", __func__);
}

void TestCase4() {
  // 99,998,082 = 7071^2 + 7071^2
  int k;
  int list[4] = {0};
  int n = 99998082;
  sum_of_squares(n, &k, list);
  assert(k == 2);
  int sum = 0;
  for (int i = 0; i < k; ++i) sum += list[i]*list[i];
  assert(sum == n);
  printf("Passed %s\n", __func__);
}

void TestCase5() {
  // 87352 = 294^2 + 30^2 + 4^2 
  int k ;
  int list[4];
  sum_of_squares(87352, &k, list);
  assert(k == 3);
  int sumOfSquares = 0;
  for(int i = 0; i < k ; i++){
    sumOfSquares += list[i]*list[i];
  }
  assert(sumOfSquares == 87352);
  printf("Passed %s\n", __func__);
}

void TestCase6() {
  // 57 = 7^2 + 2^2 + 2^2
  int k ;
  int list[4];
  sum_of_squares(57, &k, list);
  assert(k == 3);
  int sumOfSquares = 0;
  for(int i = 0; i < k ; i++){
    sumOfSquares += list[i]*list[i];
  }
  assert(sumOfSquares == 57);
  printf("Passed %s\n", __func__);
}

void TestCase7() {
  // 99999 = 315^2 + 27^2 + 6^2 + 3^2
  int k ;
  int list[4];
  sum_of_squares(99999, &k, list);
  assert(k == 4);
  // TODO: refactor the following 4 lines into
  // a helper function. Do not reuse.
  int sumOfSquares = 0;
  for(int i = 0; i < k ; i++){
    sumOfSquares += list[i]*list[i];
  }
  assert(sumOfSquares == 99999);
  printf("Passed %s\n", __func__);
}

void TestCase8(){
  // 127 = 11^2 + 2^2 + 1^2 + 1^2
  int k;
  int list[4] = {0};
  int n = 127;
  sum_of_squares(n, &k, list);
  assert(k == 4);
  int sumOfSquares = 0;
  for (int i = 0; i < k; ++i) {
    sumOfSquares += list[i] * list[i];
  }
  assert(sumOfSquares == n);
  printf("Passed %s\n", __func__);
}

int main() {
  TestCase1();
  TestCase2();
  TestCase3();
  TestCase4();
  TestCase5();
  TestCase6();
  TestCase7();
  TestCase8();
  printf("\nAll tests passed!\n");
  return 0;
}