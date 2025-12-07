#include <stdio.h>
#include <math.h>
#include <assert.h>

// Given the name of a text file, read its contents and compute the frequency
// of letters 'a' to 'z', ignoring all non-letter characters.
// Uppercase and lowercase letters are treated as the same.
// freq[0] corresponds to 'a'
// freq[1] corresponds to 'b'
// ...
// freq[25] corresponds to 'z'
void file_frequency(char *file_name, double *freq) {

}

static int double_equals(double a, double b) {
  const double EPSILON = 1e-9;
  return fabs(a - b) < EPSILON;
}

void TestCase1() {
  // test with "Alice’s_Adventures_in_Wonderland.txt"
  double total_letters = 123342;
  char *file_name = "Alice's_Adventures_in_Wonderland.txt";
  double freq[26] = {0}; // results
  double expected_freq[26] = {9837/total_letters, 1752/total_letters, 3027/total_letters,
                             5478/total_letters, 15479/total_letters, 2378/total_letters,
                             2950/total_letters, 7922/total_letters, 8640/total_letters,
                             237/total_letters, 1298/total_letters, 5213/total_letters,
                             2405/total_letters, 8071/total_letters, 9517/total_letters,
                             1975/total_letters, 223/total_letters, 6655/total_letters,
                             7270/total_letters, 12222/total_letters, 3992/total_letters,
                             968/total_letters, 2971/total_letters, 180/total_letters,
                             2603/total_letters, 79/total_letters}; // expected results

  // compare
  file_frequency(file_name, freq);
  for(int i = 0; i < 26; i++) {
    assert(double_equals(freq[i], expected_freq[i]));
  }
  printf("Passed %s\n", __func__);
}

void TestCase2() {
  // test with Romeo_and_Juliet.txt
  double total_letters = 122501;
  char *file_name = "Romeo_and_Juliet.txt";
  double freq[26] = {0}; // results
  double expected_freq[26] = {9366/total_letters, 1994/total_letters, 2970/total_letters,
                             4499/total_letters, 14827/total_letters, 2429/total_letters,
                             2289/total_letters, 7350/total_letters, 8105/total_letters,
                             382/total_letters, 979/total_letters, 5528/total_letters,
                             3693/total_letters, 7626/total_letters, 10241/total_letters,
                             2038/total_letters, 76/total_letters, 7756/total_letters,
                             7455/total_letters, 11327/total_letters, 4258/total_letters,
                             1240/total_letters, 2891/total_letters, 158/total_letters,
                             2989/total_letters, 35/total_letters}; // expected results

  // compare
  file_frequency(file_name, freq);
  for(int i = 0; i < 26; i++) {
    assert(double_equals(freq[i], expected_freq[i]));
  } 
  printf("Passed %s\n", __func__);
}

int main() {
  TestCase1();
  TestCase2();
  printf("\nAll tests passed!\n");
  return 0;
}
