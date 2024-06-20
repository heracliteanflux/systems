/*    pointer_pass_by_reference.c
 */

#include <stdio.h>

void swap (int *a, int *b) {
  int tmp =  *a;
       *a =  *b;
       *b = tmp;
}

int main (void) {
  int a = 42, b = -7;
  swap(&a, &b);
  printf("a: %d, b: %d\n", a, b);
  return 0;
}
