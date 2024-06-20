/*    pointer_double.c
 */

#include <stdio.h>

int main (int argc, char **argv) {
  char hi[6] = {'h', 'e', 'l', 'l', 'o', '\0'};
  char *p, **dp;

  p  = &hi[0]; // address of hi[0]
  dp = &p;     // address of p

  printf("%c %c\n", *p, **dp);      //   value of hi[0] h
  printf("%p %p %p\n", p, *dp, hi); // address of hi[0]
  p += 1;                           // address of hi[1]
  printf("%c %c\n", *p, **dp);      //   value of hi[1] e
  printf("%p %p %p\n", p, *dp, hi); // address of hi[1], hi = address of hi[0]
  *dp += 3; // same as p += 3          address of hi[3]
  printf("%c %c\n", *p, **dp);      //   value of hi[3] o
  printf("%p %p %p\n", p, *dp, hi); // address of hi[3], hi = address of hi[0]

  return 0;
}
