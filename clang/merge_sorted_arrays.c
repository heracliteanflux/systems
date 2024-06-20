/*    merge_sorted_arrays.c
 *   
 *    the sorted array must not contain duplicates
 */

#include <stdio.h>

void sorted_array_merge (int arr1[], int size1, int arr2[], int size2, int merged[]) {
  int i = 0,
      j = 0,
      k = 0;

  while (i < size1 && j < size2) {
    if (arr1[i] < arr2[j]) {
      merged[k++] = arr1[i++];
    }
    else if (arr2[j] < arr1[i]) {
      merged[k++] = arr2[j++];
    }
    else {
      merged[k++] = arr1[i++];
      j++;
    }
  }

  while (i < size1) {
    merged[k++] = arr1[i++];
  }

  while (j < size2) {
    merged[k++] = arr2[j++];
  }
}

int main () {
  int arr1[] = {1, 3, 5, 7};
  int size1  = sizeof(arr1) / sizeof(arr1[0]);
  int arr2[] = {2, 4, 6};
  int size2  = sizeof(arr2) / sizeof(arr2[0]);

  int merged[size1 + size2];

  sorted_array_merge(arr1, size1, arr2, size2, merged);

  printf("merged array: ");
  for (int i = 0; i < size1 + size2; i++) {
    printf("%d ", merged[i]);
  }
  printf("\n");

  return 0;
}
