/*    num_power.c
 *
 *    Write a program to calculate the power of a number.
 */

#include <stdio.h>

double power (double base, int exponent) {
  double result = 1.0;
  int abs_exponent = exponent < 0 ? -exponent : exponent;

  for (int i = 0; i < abs_exponent; i++) {
    result *= base;
  }

  if (exponent < 0) {
    result = 1.0 / result;
  }

  printf("%d power %d is %d", base, exponent, result);
  return result;
}
