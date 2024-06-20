/*    fibonacci_iterative.c
 */

#include <stdio.h>

int main () {
  int n, first = 0, second = 1, next;
  
  printf("Enter the value of n: ");
  scanf("%d", &n);

  printf("Fibonacci sequence up to %d: ", n);
  for (int i = 0; i < n; i++) {
    printf("%d", first);
    next   = first + second;
    first  = second;
    second = next;
  }

  return 0;
}
