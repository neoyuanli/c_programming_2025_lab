#include <stdio.h>
#include <assert.h>

/*
  Problem: Compute the Greatest Common Divisor (GCD) recursively.

  Given two positive integers a and b, return their greatest common divisor.
  Use Euclid's algorithm, defined as:
      gcd(a, b) = a, if b == 0
      gcd(a, b) = gcd(b, a % b), otherwise
*/
int gcd(int a, int b) {
  // TODO: COMPLETE THE CODE
}


/**
 * @brief 执行一个断言检查。
 * @param a 实际值
 * @param b 期望值
 * @param test_description 测试描述
 */
void check_gcd_equal(int a, int b, int expected, const char* test_description) {
  int actual = gcd(a, b);

  // 打印测试信息
  printf("Test: %s (gcd(%d, %d)) -> Expected: %d, Actual: %d\n",
         test_description, a, b, expected, actual);

  // 标准 C 断言：如果条件不满足，打印错误信息并终止程序
  assert(actual == expected);
}

void test_standard_cases() {
  printf("\n--- Running Standard GCD Cases ---\n");
  check_gcd_equal(10, 5, 5, "a is multiple of b");
  check_gcd_equal(48, 18, 6, "General case 48, 18");
  check_gcd_equal(17, 13, 1, "Mutually prime");
}

void test_boundary_cases() {
  printf("\n--- Running Boundary Cases (Zero) ---\n");
  // gcd(a, 0) == a
  check_gcd_equal(5, 0, 5, "b is zero");
  check_gcd_equal(0, 7, 7, "a is zero");
  // gcd(0, 0) == 0
  check_gcd_equal(0, 0, 0, "Both are zero");
}

void test_negative_cases() {
  printf("\n--- Running Negative Input Cases ---\n");
  // gcd 结果应始终为正
  check_gcd_equal(-48, 18, 6, "a is negative");
  check_gcd_equal(48, -18, 6, "b is negative");
  check_gcd_equal(-48, -18, 6, "Both are negative");
}

int main() {
  printf("======================================\n");
  printf("Running All GCD Test Scenarios (Assert Style)\n");
  printf("======================================\n");

  test_standard_cases();
  test_boundary_cases();
  test_negative_cases();

  printf("\n======================================\n");
  printf("All tests passed!\n");
  printf("======================================\n");

  return 0; // CTest Success
}
