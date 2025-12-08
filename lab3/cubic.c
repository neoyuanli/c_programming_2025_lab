#include <stdio.h>
#include <assert.h>
#include <math.h>

// Solve the cubic equation x^3 + c2*x^2 + c1*x + c0 = 0 with precision eps.
// Store the number of real roots in *cnt (possible values: 1, 2, or 3).
// Store the roots in sol[0], ..., sol[*cnt - 1], sorted in ascending order.
void solve_cubic_equ(double c2, double c1, double c0, double eps,
                     int *cnt, double *sol) {
  // TODO: Implement
}

// Compares two double numbers x and y for equality within a specified tolerance eps.
// Returns 1 if the absolute difference between x and y is less than eps, 0 otherwise.
int compare_equal(double x, double y, double eps) {
  if (fabs(x - y) < eps) return 1;
  else return 0;
}

void TestCase1() {
  // Test Case 1: x^3 - 1 = 0, only one real root x = 1
  double eps = 1e-6;
  int cnt;
  double sol[3];
  solve_cubic_equ(0, 0, -1, eps, &cnt, sol);
  printf("Test Case 1: Expected 1 root, x = 1\n");
  printf("Number of roots: %d\n", cnt);
  for (int i = 0; i < cnt; i++) {
      printf("Root %d: %.6f\n", i + 1, sol[i]);
  }
  assert(cnt == 1);
  assert(compare_equal(sol[0], 1.0, eps));
  printf("Passed TestCase1\n");
}

void TestCase2() {
  // Test Case 2: (x - 1)^2(x + 2) = 0, two real roots x = 1 (double root), x = -2
  double eps = 1e-6;
  int cnt;
  double sol[3];
  solve_cubic_equ(0, -3, 2, eps, &cnt, sol);
  printf("Test Case 2: Expected 2 root, x = 1 (double), x = -2\n");
  printf("Number of roots: %d\n", cnt);
  for (int i = 0; i < cnt; i++) {
    printf("Root %d: %.6f\n", i + 1, sol[i]);
  }
  assert(cnt == 2);
  assert(compare_equal(sol[0], -2.0, eps));
  assert(compare_equal(sol[1], 1.0, eps));
  printf("Passed TestCase2\n");

}

void TestCase3() {
  // Test Case 3: x^3 - 6x^2 + 11x - 6 = 0, three real roots x = 1, 2, 3
  double eps = 1e-6;
  int cnt;
  double sol[3];
  solve_cubic_equ(-6, 11, -6, eps, &cnt, sol);
  printf("Test Case 3: Expected 3 roots, x = 1, 2, 3\n");
  printf("Number of roots: %d\n", cnt);
  for (int i = 0; i < cnt; i++) {
    printf("Root %d: %.6f\n", i + 1, sol[i]);
  }
  assert(cnt == 3);
  assert(compare_equal(sol[0], 1, eps));
  assert(compare_equal(sol[1], 2, eps));
  assert(compare_equal(sol[2], 3, eps));
  printf("Passed TestCase3\n");
}

int main() {
  TestCase1();
  TestCase2();
  TestCase3();

  printf("\nAll tests passed!\n");
  return 0;
}
