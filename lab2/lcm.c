#include <stdio.h>
#include <assert.h>

// Compute and return the least common multiple (LCM) of
// three integers: a, b, and c.
// remeber to transform negative numbers to positive ones.
// when one of the numbers is 0, return 0.
int lcm(int a, int b, int c) {
    // TODO: implement
}

void TestLcmCase1(int (*lcm)(int, int, int)) {
  int a = 4, b = 5, c = 6;
  int result = lcm(a, b, c);
  assert(result == 60);
  printf("Passed %s\n", __func__);
}

void TestLcmCase2(int (*lcm)(int, int, int)) {
  int a = 2, b = 2, c = 2;
  int result = lcm(a, b, c);
  assert(result == 2);
  printf("Passed %s\n", __func__);
}

void TestLcmCase3(int (*lcm)(int, int, int)) {
  int a = 0, b = 5, c = 10;
  int result = lcm(a, b, c);
  assert(result == 0);
  printf("Passed %s\n", __func__);
}

void TestLcmCase4(int (*lcm)(int, int, int)) {
  int a = -4, b = 5, c = 6;
  int result = lcm(a, b, c);
  assert(result == 60);
  printf("Passed %s\n", __func__);
}

void TestLcmCase5(int (*lcm)(int, int, int)) {
  int a = 7, b = 2, c = 14;
  int result = lcm(a, b, c);
  assert(result == 14);
  printf("Passed %s\n", __func__);
}

int main() {
  TestLcmCase1(lcm);
  TestLcmCase2(lcm);
  TestLcmCase3(lcm);
  TestLcmCase4(lcm);
  TestLcmCase5(lcm);
  printf("\nAll tests passed!\n");
  return 0;
}
