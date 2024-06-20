/*    array_find_second_largest.c
 *
 *    the input array must contain at least two elements
 */

#include <stdio.h>

int find_second_largest (int arr[], int size) {
  int        largest = arr[0];
  int second_largest = arr[0];

  for (int i = 1; i < size; i++) {
         if  (arr[i] >                              largest)  { second_largest = largest; largest = arr[i]; }
    else if ((arr[i] >   second_largest && arr[i] < largest)
          || (largest == second_largest && arr[i] < largest)) { second_largest                    = arr[i]; }
  }

  return second_largest;
}

int main () {
  int arr[] = {10, 5, 8, 2, 7};
  int size  = sizeof(arr) / sizeof(arr[0]);

  printf("sizeof(arr)=%lu sizeof(arr[0])=%lu size=%d\n", sizeof(arr), sizeof(arr[0]), size);

  int second_largest = find_second_largest(arr, size);

  printf("Second largest element: %d\n", second_largest);

  return 0;
}
