#include <stdio.h>
#include <assert.h>
#include <math.h>

const double EPSILON = 1e-6;

typedef void (*fun_t)(double*, double*);

// Swap two doubles
void swap(double *x, double *y) {
  // Write your code here.
}

int double_equal(double a, double b) {
  return fabs(a - b) < EPSILON;
}

void TestSwapCase1(fun_t swap) {
  double x = 1.00;
  double y = 1.00;
  swap(&x, &y);
  assert(double_equal(x, 1.00));
  assert(double_equal(y, 1.00));
  printf("Passed %s\n", __func__);
}

void TestSwapCase2(fun_t swap) {
  double x = 1.00;
  double y = 2.00;
  swap(&x, &y);
  assert(double_equal(x, 2.00));
  assert(double_equal(y, 1.00));
  printf("Passed %s\n", __func__);
}

void TestSwapCase3(fun_t swap) {
  double x = -5.50;
  double y = 8.30;
  swap(&x, &y);
  assert(double_equal(x, 8.30));
  assert(double_equal(y, -5.50));
  printf("Passed %s\n", __func__);
}

void TestSwapCase4(fun_t swap) {
  double x = 42;
  swap(&x, &x);
  assert(double_equal(x, 42));
  printf("Passed %s\n", __func__);
}

int main() {
  TestSwapCase1(swap);
  TestSwapCase2(swap);
  TestSwapCase3(swap);
  TestSwapCase4(swap);
  printf("\nAll tests passed!\n");
  return 0;
}
