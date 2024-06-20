/*    array_find_min.c
 *
 *    Write a program to find the smallest element in a given array of integers.
 */

#include <stdio.h>

int find_smallest (int array[], int length) {
  if (length == 0) {
    printf("array is empty.\n");
    return 0;
  }

  int smallest = array[0];
  for (int i = 1; i < length; i++) {
    if (array[i] < smallest) {
      smallest = array[i];
    }
  }

  printf("smallest element in the array is %d", smallest);
  return smallest;
}
