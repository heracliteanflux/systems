/*    rotate_array.c
 *
 *    rotate an array by a number of steps
 *    the input array must contain more elements than there are steps
 */

#include <stdio.h>

void rotate_array (int arr[], int size, int steps) {
  int temp;

  for (int i = 0; i < steps; i++) {
    temp = arr[size - 1];                 // first_elem <-- temp <-- last_elem
    for (int j = size - 1; j > 0; j--) {
      arr[j] = arr[j - 1]; 
    }
    arr[0] = temp;
  }
}

int main () {
  int arr[] = {1, 2, 3, 4, 5};
  int size  = sizeof(arr) / sizeof(arr[0]);
  int steps = 2;

  rotate_array(arr, size, steps);

  printf("Rotated array: ");
  for (int i = 0; i < size; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");

  return 0;
}
