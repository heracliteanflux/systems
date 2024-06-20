/*    union_int_or_float.c
 *
 *    Define a union called `Number` which stores either an int or a float.
 *    Prompt the user to enter a number and specify its type as follows: 1 for int, 2 for float.
 *    Based on the user's choice, store the number in the appropriate member of the union and display the stored value.
 */

#include <stdio.h>

union Number {
  int   int_val;
  float flt_val;
};

int main () {
  union Number num;
  int          choice;

  printf("Would you like to enter an int or a float?\n[`1` for int, `2` for float]: ");
  scanf("%d", &choice);

  if (choice == 1) {
    printf("Enter an int: ");
    scanf("%d", &num.int_val);

    printf("The stored int value is %d\n", num.int_val);
  }
  else if (choice == 2) {
    printf("Enter a float: ");
    scanf("%f", &num.flt_val);

    printf("The stored float value is %.2f\n", num.flt_val);
  }
  else {
    printf("Invalid choice! Exiting...\n");
  }

  return 0;
}