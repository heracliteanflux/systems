/*    array.c
 *
 */

#include <stdio.h>

int main () {
  // Unspecified values are given a default value of 0
  int arr[10] = {1, 2, 3};

  for (int i = 0; i < 10; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");
  // `1 2 3 0 0 0 0 0 0 0`


  // The name of an array can be used as a pointer to the 0-th element of the array
  int arr2[6] = { [0 ... 5] = 42 };
  
  printf("%d\n", *arr2);   // `42`
  *arr2 = 10;              // assign the value 10 to the first element of the array
  for (int i = 0; i < 6; i++) {
    printf("%d ", arr2[i]);
  }
  printf("\n");
  // `10 42 42 42 42 42`
  

  return 0;
}
