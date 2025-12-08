#include <assert.h>
#include <math.h>
#include <stdio.h>

/*
  Let p be a prime.  The multiplicative group modulo p is
    Z_p^* = {1, 2, ..., p-1},
  with operation multiplication (mod p).

  Given p (prime) and n with 1 <= n <= p-1, find the modular inverse of n.
  That is, find x (1 <= x <= p-1) such that
    n * x = 1 (mod p).
*/
int inverse(int n, int p) {
  // TODO: COMPLETE THE FUNCTION
}

// ----------------------------------------------------
// 2. 测试工具函数
// ----------------------------------------------------

/**
 * @brief 执行一个模逆元检查。
 * 验证 n * inverse(n, p) = 1 (mod p) 是否成立。
 *
 * @param n 待求逆元的数
 * @param p 模数
 * @param test_description 测试描述
 */
void check_inverse(int n, int p, const char* test_description) {
  int x = inverse(n, p);
  long long result = (long long)n * x;
  long long actual_mod = result % p;

  // 打印测试信息
  printf("Test: %s (n=%d, p=%d) -> Inverse x=%d\n",
         test_description, n, p, x);

  // 1. 验证核心属性: n * x = 1 (mod p)
  assert(actual_mod == 1);

  // 2. 验证逆元 x 的范围: 1 <= x <= p-1
  assert(x >= 1 && x <= p - 1);
}

// ----------------------------------------------------
// 3. 测试场景函数
// ----------------------------------------------------

void test_small_prime_p7() {
  int p = 7;
  printf("\n--- Running Tests for p = 7 ---\n");

  // 逆元总是 1
  check_inverse(1, p, "Boundary: n=1");

  // 2*4 = 8 = 1 (mod 7)
  check_inverse(2, p, "Standard: n=2");

  // 3*5 = 15 = 1 (mod 7)
  check_inverse(3, p, "Standard: n=3");

  // 6*6 = 36 = 1 (mod 7)
  check_inverse(6, p, "Boundary: n=p-1");
}

void test_medium_prime_p17() {
  int p = 17;
  printf("\n--- Running Tests for p = 17 ---\n");

  check_inverse(5, p, "Medium: n=5");
  // 5 * x = 1 (mod 17). x=7 (5*7=35, 35%17=1)
  check_inverse(7, p, "Medium: n=7"); // 7 * x = 1 (mod 17). x=5
  check_inverse(16, p, "Boundary: n=p-1 (16)"); // 16 * 16 = 256 = 1 (mod 17)
}

void test_larger_prime_p97() {
  int p = 97;
  printf("\n--- Running Tests for p = 97 ---\n");

  // 逆元必须计算: 19 * x = 1 (mod 97)
  check_inverse(19, p, "Larger: n=19"); // x = 46 (19*46 = 874, 874%97=1)

  // n 接近 p/2
  check_inverse(48, p, "Larger: n=48"); // x = 89
}


// ----------------------------------------------------
// 4. 主程序
// ----------------------------------------------------

int main() {
  printf("======================================\n");
  printf("Running All Modular Inverse Test Scenarios\n");
  printf("======================================\n");

  test_small_prime_p7();
  test_medium_prime_p17();
  test_larger_prime_p97();

  printf("\n======================================\n");
  printf("All tests passed!\n");
  printf("======================================\n");

  return 0; // CTest Success
}
