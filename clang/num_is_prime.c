/*    num_is_prime.c
 */

#include <stdio.h>

int main () {
  int num, isPrime = 1;

  printf("Enter a number: ");
  scanf("%d", &num);

  for (int i = 2; i <= num/2; i++) {
    if (num % i == 0) {
      isPrime = 0;
      break;
    }
  }

  if (isPrime == 1) {
    printf("prime");
  }
  else {
    printf("not prime");
  }

  return 0;
}
