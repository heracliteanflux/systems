/*    pointer_concat_two_strings.c
 */

#include <stdio.h>

void concat_strings (char *str1, char *str2) {
  while (*str1) {
    str1++;
  }
  while (*str2) {
    *str1 = *str2;
    str1++;
    str2++;
  }
  *str1 = '\0';
}

int main () {
  char str1[100] = "Hello";
  char str2[]    = ", World!";

  printf("Before concatenation: %s\n", str1);
  concat_strings(str1, str2);
  printf("After  concatenation: %s\n", str1);

  return 0;
}
