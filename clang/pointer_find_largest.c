/*    pointer_find_largest.c
 */

#include <stdio.h>

int find_largest (int *arr, int size) {
  int largest = *arr;

  for (int i = 1; i < size; i++) {
    if (*(arr + i) > largest) {
      largest = *(arr + i);
    }
  }

  return largest;
}

int main () {
  int arr[]   = {10, 5, 8, 2, 7};
  int size    = sizeof(arr) / sizeof(arr[0]);
  int largest = find_largest(arr, size);

  printf("Largest element: %d\n", largest);

  return 0;
}
