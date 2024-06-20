/*    num_factorial_recursive.c
 */

#include <stdio.h>

int factorial (int n) {
  if (n == 0) {
    return 1;
  }
  else {
    return n * factorial(n - 1);
  }
}

int main () {
  int num;

  printf("Enter a number: ");
  scanf("%d", &num);

  printf("factorial of %d is %d", num, factorial(num));

  return 0;
}
