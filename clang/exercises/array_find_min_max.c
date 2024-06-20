/*    array_find_min_max.c
 *
 *    returns the largest and the smallest elements in the array
 *    the array must contain at least one element
 */

#include <stdio.h>

void find_min_max (int arr[], int size) {
  int min = arr[0];
  int max = arr[0];

  for (int i = 0; i < size; i++) {
    if (arr[i] < min) {
      min = arr[i];
    }
    if (arr[i] > max) {
      max = arr[i];
    }
  }

  printf("Minimum element: %d\n", min);
  printf("Maximum element: %d\n", max);
}

int main () {
  int arr[] = {10, 5, 8, 2, 7};
  int size  = sizeof(arr) / sizeof(arr[0]);

  find_min_max(arr, size);

  return 0;
}
