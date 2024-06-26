/*    sort_bubble.c
 */

void bubble_sort (int array[], int length) {
  for (int i = 0; i < length - 1; i++) {
    for (int j = 0; j < length - 1 - i; j++) {
      if (array[j] > array[j + 1]) {
        // swap array[j] and array[j + 1]
        int temp     = array[j];
        array[j]     = array[j + 1];
        array[j + 1] = temp;
      }
    }
  }
}
