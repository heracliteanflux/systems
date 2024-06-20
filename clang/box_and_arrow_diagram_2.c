/*    box_and_arrow_diagram_2.c
 */

#include <stdio.h>

int main (int argc, char **argv) {
  int x      = 1;
  int arr[3] = {2, 3, 4};
  int *p     = &arr[1];   // address of arr[1]
  int **dp   = &p;        // address of p
  
  for (int i = 0; i < 3; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");

  **dp += 1;              // increment value of arr[1]: 3 -> 4
  p += 1;                 // address of arr[2]
  **dp += 1;              // increment value of arr[2]: 4 -> 5

  for (int i = 0; i < 3; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");

  return 0;
}
