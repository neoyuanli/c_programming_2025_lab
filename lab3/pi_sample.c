#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

/*
Sample random points (x, y) uniformly from the square [-1, 1] × [-1, 1].
Let C be the unit circle centered at (0, 0) with radius 1.
The probability that a sampled point lies inside C is exactly PI / 4.

Use Monte Carlo sampling with 'count' points to estimate the value of PI.
Return the estimated value.
*/
double sample_pi(int count) {
  // TODO: implement
}

/**
 * @brief Calculates the confidence interval for a PI estimate given the number
 * of samples and an acceptable failure probability.
 * @param count The total number of Monte Carlo samples.
 * @param failure_prob The maximum acceptable probability that the test will
 * fail due to randomness (e.g., 1e-9).
 * @param lower_bound A pointer to store the calculated acceptable lower bound.
 * @param upper_bound A pointer to store the calculated acceptable upper bound.
 */
void calculate_pi_bounds(long long count, double failure_prob,
                         double* lower_bound, double* upper_bound) {
  if (count <= 0 || failure_prob <= 0.0 || failure_prob >= 1.0) {
    *lower_bound = 1.0;
    *upper_bound = 0.0;
    return;
  }

  const double true_p = M_PI / 4.0;
  const double mu = count * true_p;

  const double delta = sqrt((3.0 * log(2.0 / failure_prob)) / mu);

  *lower_bound = M_PI * (1.0 - delta);
  *upper_bound = M_PI * (1.0 + delta);
}

/**
 * @brief Runs a standalone PI estimation test case and verifies the result.
 *
 * @param test_name The name of the test case.
 * @param count The total number of Monte Carlo samples.
 * @param failure_prob The maximum acceptable probability that the test will
 * fail due to randomness.
 */
void run_pi_test_case(const char* test_name, long long count,
                      double failure_prob) {
  printf("--- Running Test Case: %s ---\n", test_name);

  double lower_bound, upper_bound;
  calculate_pi_bounds(count, failure_prob, &lower_bound, &upper_bound);

  printf("Number of samples: %lld\n", count);
  printf("Desired max failure probability: %e\n", failure_prob);
  printf("Calculated acceptable range: [%.8f, %.8f] (Width: %.8f)\n",
         lower_bound, upper_bound, upper_bound - lower_bound);

  double pi_estimate = sample_pi((int)count);
  printf("PI estimate from simulation: %.8f\n", pi_estimate);

  assert(pi_estimate >= lower_bound && "Estimate was too low.");
  assert(pi_estimate <= upper_bound && "Estimate was too high.");

  printf(
      "Passed: The estimate is within the calculated high-confidence "
      "bounds.\n\n");
}

void test_all_pi_scenarios() {
  printf("=============================================\n");
  printf("Running All Pi Estimation Test Scenarios\n");
  printf("=============================================\n\n");

  run_pi_test_case("High Precision", 5000000, 1e-9);

  run_pi_test_case("Medium Precision", 500000, 1e-7);

  run_pi_test_case("Quick / Low Precision", 50000, 0.01);  // 1% 的失败概率
}

int main() {
  test_all_pi_scenarios();
  printf("\nAll tests passed!\n");
  return 0;
}
