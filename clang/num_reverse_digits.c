/*    num_reverse_digits.c
 *
 *    Reverse the digits of an integer number.
 */

#include <stdio.h>

int reverse_number (int num) {
  int reversed_num = 0;

  while (num != 0) {
    int digit = num % 10;                     // extract the last digit from the original number
    reversed_num = reversed_num * 10 + digit;
    //             ^^^^^^^^^^^^^^^^^             left-shift preexisting digits
    //                                 ^^^^^     append new digit
    num /= 10;                                // remove  the last digit from the original number
  }

  return reversed_num;
}

int main () {
  int num;
  printf("Enter an integer number: ");
  scanf("%d", &num);

  int reversed = reverse_number(num);
  printf("Reversed number: %d\n", reversed);

  return 0;
}
