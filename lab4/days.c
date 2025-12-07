#include <stdio.h>
#include <assert.h>

// Converts a given date (year, month, day) to the total number of days 
// since January 1, Year 1. 
// Returns -1 if the date is invalid.
int date_to_days(int year, int month, int day) {

}

void TestCase1() {
  // Test Case 1: 2016.2.29
  int days;
  days = date_to_days(2016,2,29);
  assert(days == 736022);
  printf("Passed %s\n", __func__);
}

void TestCase2() {
  // Test Case 1: 2017.2.29
  int days;
  days = date_to_days(2017,2,29);
  assert(days == -1);
  printf("Passed %s\n", __func__);
}

void TestCase3() {
  // Test Case 3: 2024.10.12
  int days;
  days=date_to_days(2024,10,12);
  assert(days == 739170);
  printf("Passed %s\n", __func__);
}

void TestCase4() {
  // Test Case 4: Century non-leap year 1900-02-29 (should be invalid)
  int days = date_to_days(1900,2,29);
  assert(days == -1);
  printf("Passed %s\n", __func__);
}

void TestCase5() {
  // Months with 30 days to check
  int months_with_30_days[] = {4, 6, 9, 11};
  int year = 2024;  // Choose any common year or leap year

  for (int i = 0; i < 4; i++) {
    int month = months_with_30_days[i];
    int day = 31;  // Days exceeding the number of days in that month

    int result = date_to_days(year, month, day);

    // Should return -1 (indicating an invalid date)
    assert(result == -1 );
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

