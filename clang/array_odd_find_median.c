/*    array_odd_find_median.c
 */

#include <stdio.h>

void swap (int *a, int *b) {
  int temp =   *a;
        *a =   *b;
        *b = temp;
}

int find_median (int arr[], int size) {

  // bubble sort
  for (int i = 0; i < size - 1; i++) {
    for (int j = 0; j < size - i - 1; j++) {
      if (arr[j] > arr[j + 1]) {
        swap(&arr[j], &arr[j + 1]);
      }
    }
  }

  return arr[size / 2];
}

int main () {
  int arr[]  = {3, 1, 5, 2, 4};
  int size   = sizeof(arr) / sizeof(arr[0]);
  
  printf("original array: ");
  for (int i = 0; i < size; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");

  int median = find_median(arr, size);
  printf("sorted   array: ");
  for (int i = 0; i < size; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");

  printf("median: %d\n", median);

  return 0;
}
