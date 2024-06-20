/*    memcpy_practice.c
 */

#include <stdio.h>
#include <string.h>
#include <stdint.h>

// print an array of chars
void print_char_array (const char *arr, size_t size) {
  //                   ^^^^^^^^^^^^^^^   pointer to an array of constant chars
  for (int i = 0; i < size; ++i)
    printf("%c ", arr[i]);
  printf("\n");
}

// copy elems from array `src` to array `dst` via function `memcpy`
void copy_whole_array (char *src, char *dst, int copy_length) {
  memcpy(dst, src, copy_length);
}

// copy the string from string `src_str` to string `dst_str` via function `memcpy` and include the null terminator
void copy_whole_string (char *src_str, char *dst_str, int copy_length) {
  memcpy(dst_str, src_str, copy_length);
}

// copy length elems from idx 0 in array `src_partial` to array `dst_partial` via function `memcpy`
void copy_partial_array (char *src_partial, char *dst_partial, int copy_length) {
  memcpy(dst_partial, src_partial, copy_length);
}

// copy length elems from idx 3 in array `src_partial` to array `dst_partial` via function `memcpy`
void copy_partial_array_1 (char *src_partial, char *dst_partial, int copy_length) {
  memcpy(dst_partial, src_partial + 3, copy_length);
}

// copy elems from array `src1` to array `dst` following the pattern of copying 2 elems and skipping 1 elem and repeating until the required size is achieved via function `memcpy`
void copy_multiple_3_indices (char *src1, char *dst, int src_length, int required_size) {
  int copied_elements = 0;
  int start_idx = 0;
  int dst_idx = 0;

  while (copied_elements < required_size) {
    for (int i = 0; i < src_length; ) {
      int elements_to_copy = 2;
      memcpy(dst + dst_idx, src1 + start_idx, 2);
      dst_idx += elements_to_copy;
      start_idx += 3;
      copied_elements += elements_to_copy;
      i += 3;
    }
  }
}

int main () {
  // 1 - array of chars
  char src[] = {'1', '2', '3', '4', '5'};
  char dst[5];
  copy_whole_array(src, dst, 5);
  printf("EXERCISE 1 - array of chars\n");
  printf("src: ");
  print_char_array(src, 5);
  printf("dst: ");
  print_char_array(dst, 5);
  printf("\n");

  // 2 - string
  char src_str[] = "Hello, world!";
  char dst_str[20];
  copy_whole_string(src_str, dst_str, 14);
  printf("EXERCISE 2 - string\n");
  printf("src: %s\n", src_str);
  printf("dst: %s\n", dst_str);
  printf("\n");

  // 3 - portion of an array
  char src_partial[] = {'a', 'b', 'c', 'd', 'e', 'i', 'o', 'u'};
  char dst_partial[4];
  copy_partial_array(src_partial, dst_partial, 3);
  printf("EXERCISE 3 - portion of an array\n");
  printf("src: ");
  print_char_array(src_partial, 8);
  printf("dst: ");
  print_char_array(dst_partial, 3);
  printf("\n");

  // 4 - portion of an array
  char dst_partial2[4];
  copy_partial_array_1(src_partial, dst_partial2, 4);
  printf("EXERCISE 4 - portion of an array\n");
  printf("src: ");
  print_char_array(src_partial, 8);
  printf("dst: ");
  print_char_array(dst_partial2, 4);
  printf("\n");

  // 5 - portion of an array
  char src1[15] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o'};
  char dst2[6];
  int required_size = 6;
  copy_multiple_3_indices(src1, dst2, 15, required_size);
  printf("EXERCISE 5 - portion of an array\n");
  printf("src: ");
  print_char_array(src1, 15);
  printf("dst: ");
  print_char_array(dst2, 6);
  printf("\n");

  return 0;
}