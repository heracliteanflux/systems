/*    pointer_swap.c
 *
 *    Write a program that takes pointers to two integers and swaps the values of the integers.
 */

#include <stdio.h>

void swap (int *a, int *b) {
  printf("before swapping : a = %d, b = %d", *a, *b);
  int temp =   *a;   // b <-- temp <-- a
        *a =   *b;   // a <--          b
        *b = temp;
  printf("after  swapping : a = %d, b = %d", *a, *b);
}
