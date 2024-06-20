/*    str_count_consonants_and_vowels.c
 */

#include <ctype.h>
#include <stdio.h>

void count_consonants_and_vowels (const char *str, int *consonants, int *vowels) {
//                                ^^^^^   Why do we use `const` here?
  *consonants = 0;
  *vowels     = 0;

  while (*str) {                  // iterate until the pointer points to the null character `\0` terminating the character array
    char ch = tolower(*str);      // convert the character to lowercase
    if (ch >= 'a' && ch <= 'z') { // if the character is a letter
      if (ch == 'a' ||
          ch == 'e' ||
          ch == 'i' ||
          ch == 'o' ||
          ch == 'u')
        (*vowels)++;              // add one to the vowel count
      else
        (*consonants)++;          // add one to the consonant count
    }
    str++;                        // increment the pointer to the next character in the character array
  }
}

int main () {
  char str[100];   // 100 B
  int  consonants,
       vowels;

  printf("Enter a string: ");
  fgets(str, sizeof(str), stdin);

  count_consonants_and_vowels(str, &consonants, &vowels);

  printf("number of consonants: %d\n", consonants);
  printf("number of vowels:     %d\n", vowels);

  return 0;
}