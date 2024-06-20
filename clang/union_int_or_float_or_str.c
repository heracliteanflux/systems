/*    union_int_or_float_or_str.c
 *
 *    Define a union called `Data` with three members: an int, a float, and a 20 character array.
 *    Prompt the user to enter a choice: 1 for int, 2 for float, 3 for character array.
 *    Based on the user's choice, store and display the corresponding data.
 */

#include <stdio.h>

union Data {            // 32/64
  int   int_data;       //     4 B
  float flt_data;       //     4 B
  char  str_data[20];   //    20 B
};

int main () {
  union Data data;
  int        choice;

  printf("Would you like to enter an int, a float, or a string?\n[`1` for int, `2` for float, `3` for str]: ");
  scanf("%d", &choice);

  if (choice == 1) {
    printf("Enter an int: ");
    scanf("%d", &data.int_data);

    printf("The stored int value is %d\n", data.int_data);
  }
  else if (choice == 2) {
    printf("Enter a float: ");
    scanf("%f", &data.flt_data);

    printf("The stored float value is %.2f\n", data.flt_data);
  }
  else if (choice == 3) {
    printf("Enter a string: ");
    scanf("%s", &data.str_data);

    printf("The stored string value is %s\n", data.str_data);
  }
  else {
    printf("Invalid choice! Exiting...\n");
  }

  return 0;
}
