/*    pointer_reverse_string.c
 *
 *    This program uses pointers to reverse a string.
 */

#include <stdio.h>
#include <string.h>

void reverse_string (char *str) {
  int  length = strlen(str);
  char *start = str;
  char *end   = str + length - 1;

  while (start < end) {
    char temp   = *start;
         *start =   *end;
         *end   =   temp;

    start++;
    end--;
  }
}

int main () {
  char str[] = "Hello world!";

  printf("Before reverse: %s\n", str);
  reverse_string(str);
  printf("After  reverse: %s\n", str);

  return 0;
}
