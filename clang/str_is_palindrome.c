/*    str_is_palindrome.c
 *
 *    Determine whether a string is a palindrome.
 */

#include <stdio.h>
#include <string.h>

int main () {
  char str[100];
  int  i, j, isPalindrome = 1;

  printf("Enter a string: ");
  gets(str);

  j = strlen(str) - 1;
  for (i = 0; i < j; i++; j--) {
    if (str[i] != str[j]) {
      isPalindrome = 0;
      break;
    }
  }

  if (isPalindrome == 1) {
    printf("palindrome");
  }
  else {
    printf("not palindrome");
  }

  return 0;
}
