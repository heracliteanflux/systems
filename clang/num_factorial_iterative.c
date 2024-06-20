/*    num_factorial_iterative.c
 */

#include <stdio.h>

int main () {
  int n, factorial = 1;

  printf("Enter a number: ");
  scanf("%d", &n);

  for (int i = 1; i <= n; i++) {
    factorial *= i;
  }

  printf("factorial of %d is %d", n, factorial);
  return 0;
}

//int factorial (int n) {
//  int result = 1;
//  for (int i = 1; i <= n; i++) {
//    result *= i;
//  }
//  printf("factorial of %d is %d", n, result);
//  return result;
//}
