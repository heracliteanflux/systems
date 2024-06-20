/*    dec_to_bin.c
 */

#include <stdio.h>

void dec_to_bin (int num) {
  int bin[32];
  int idx = 0;

  while (num > 0) {
    bin[idx++] = num % 2;
    num /= 2;
  }

  printf("binary representation: ");
  if (idx == 0)                          // for the case when the decimal number 0 was entered
    printf("0");
  for (int i = idx - 1; i >= 0; i--) {   // iterate over `bin` in reverse
    printf("%d", bin[i]);
  }
  printf("\n");
}

int main () {
  int num;

  printf("Enter a decimal number: ");
  scanf("%d", &num);

  dec_to_bin(num);

  return 0;
}