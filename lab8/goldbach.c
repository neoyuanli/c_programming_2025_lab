#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <math.h>

const double EPS = 1e-8;

/*
Goldbach's conjecture states that every even natural
number greater than 2 is the sum of two prime numbers.

Given an even natural number greater than 2, find two
primes (*prime1) and (*prime2) such that
n = (*prime1) + (*prime2), where n <= 10^8.
*/
void sum_of_two_primes(int n, int* prime1, int* prime2) {

}

bool is_prime(int n) {
  if (n <= 1) {
    return false;  
  }
  
  int limit = (int) (sqrt(n) + EPS);
  for (int i = 2; i <= limit; i++) {
    if (n % i == 0) {
      return false; 
    }
  }

  return true;  
}

void TestCase1() {
  // Test case 1: 10 
  int prime1, prime2;
  sum_of_two_primes(10, &prime1, &prime2);
  assert(is_prime(prime1) && is_prime(prime2) && (prime1+prime2 == 10));
  printf("Passed TestCase1\n");
}

void TestCase2() {
  // Test case 2: 2828 
  int prime1, prime2;
  sum_of_two_primes(2828, &prime1, &prime2);
  assert(is_prime(prime1) && is_prime(prime2) && (prime1+prime2 == 2828));
  printf("Passed TestCase2\n");
}

void TestCase3() {
  // Test case 3: 82828
  int prime1, prime2;
  sum_of_two_primes(82828, &prime1, &prime2);
  assert(is_prime(prime1) && is_prime(prime2) && (prime1+prime2 == 82828));
  printf("Passed TestCase3\n");
}

void TestCase4() {
  // Test case 3: 4
  int prime1, prime2;
  sum_of_two_primes(4, &prime1, &prime2);
  assert(is_prime(prime1) && is_prime(prime2) && (prime1 + prime2 == 4));
  printf("Passed TestCase4\n");
}

void TestCase5() {
  // Test case 5: 12345678
  int prime1, prime2;
  sum_of_two_primes(12345678, &prime1, &prime2);
  assert(is_prime(prime1) && is_prime(prime2) && (prime1 + prime2 == 12345678));
  printf("Passed TestCase5\n");
}

void TestCase6() {
  // maximum allowed n = 156
  int prime1, prime2;
  sum_of_two_primes(156, &prime1, &prime2);
  assert(is_prime(prime1) && is_prime(prime2) && (prime1 + prime2 == 156));
  printf("Passed TestCase6\n");
}

int main() {
  TestCase1();
  TestCase2();
  TestCase3();
  TestCase4();
  TestCase5();
  TestCase6();
  printf("\nAll tests passed!\n");
  return 0;
}