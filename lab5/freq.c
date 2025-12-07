#include <stdio.h>
#include <assert.h>
#include <math.h>

// Given a string, compute the frequency of letters 'a' to 'z',
// ignoring all non-letter characters.
// Uppercase and lowercase letters are treated as the same.
// freq[0] corresponds to 'a'
// freq[1] corresponds to 'b'
// ...
// freq[25] corresponds to 'z'
void frequency(char *str, double *freq) {

}

static int double_equals(double a, double b) {
  const double EPSILON = 1e-9;
  return fabs(a - b) < EPSILON;
}

void TestCase1() {
  // test with "Hello, World!"
  char *str = "Hello, World!";
  double freq[26] = {0};  // freq[26] is used to store the results
  double expected_freq[26] = {0}; // expected_freq[26] is used to store expected results
  expected_freq['h' - 'a'] = 1.0 / 10;
  expected_freq['e' - 'a'] = 1.0 / 10;
  expected_freq['l' - 'a'] = 3.0 / 10;
  expected_freq['o' - 'a'] = 2.0 / 10;
  expected_freq['r' - 'a'] = 1.0 / 10;
  expected_freq['w' - 'a'] = 1.0 / 10;
  expected_freq['d' - 'a'] = 1.0 / 10;
  frequency(str, freq);
  for(int i = 0; i < 26; i++) {
    assert(double_equals(freq[i], expected_freq[i])); // compare
  }
  printf("Passed %s\n", __func__);
}

void TestCase2() {
  //test with "AaBbCc"
  char *str = "AaBbCc";
  double freq[26] = {0}; // results
  double expected_freq[26] = {0}; // expected results
  expected_freq['a' - 'a'] = 2.0 / 6;
  expected_freq['b' - 'a'] = 2.0 / 6;
  expected_freq['c' - 'a'] = 2.0 / 6;
  frequency(str, freq);
  for(int i = 0; i < 26; i++) {
    assert(double_equals(freq[i], expected_freq[i])); // compare
  }
  printf("Passed %s\n", __func__);
}

void TestCase3() {
  // test with empty string
  char *str = ""; // empty string
  double freq[26] = {0}; // results
  double expected_freq[26] = {0}; // expected results
  frequency(str, freq);
  for(int i = 0; i < 26; i++) {
    assert(double_equals(freq[i], expected_freq[i])); // compare
  }
  printf("Passed %s\n", __func__);
}

void TestCase4() {
  // test with all letters
  char *str = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
  double freq[26] = {0}; // results
  double expected_freq[26] = {0}; // expected results
  for (int i = 0; i < 26; i++) {
    expected_freq[i] = 2.0 / 52; // each letter appears twice
  }
  frequency(str, freq);
  for(int i = 0; i < 26; i++) {
    assert(double_equals(freq[i], expected_freq[i])); // compare
  }
  printf("Passed %s\n", __func__);
}

void TestCase5() {
  // test whit mixed case and repeated letters
  char *str = "MMmmNnnOOOopPPpQRRrrrrr";
  double freq[26] = {0}; // results
  double expected_freq[26] = {0}; // expected results
  expected_freq['m' - 'a'] = 4.0 / 23;
  expected_freq['n' - 'a'] = 3.0 / 23;
  expected_freq['o' - 'a'] = 4.0 / 23;
  expected_freq['p' - 'a'] = 4.0 / 23;
  expected_freq['q' - 'a'] = 1.0 / 23;
  expected_freq['r' - 'a'] = 7.0 / 23;
  frequency(str, freq);
  for(int i = 0; i < 26; i++) {
    assert(double_equals(freq[i], expected_freq[i])); // compare
  }
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