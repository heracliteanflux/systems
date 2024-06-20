/*    struct_rectangle.c
 *
 *    Define a struct called Rectangle with members length and width.
 *    Prompt the user to enter a length and a width, and then calculate the area.
 */

#include <stdio.h>

struct Rectangle {
  float length;
  float width;
};

int main () {
  struct Rectangle rect;

  printf("Enter the length of the rectangle: ");
  scanf("%f", &rect.length);

  printf("Enter the width  of the rectangle: ");
  scanf("%f", &rect.width);

  float area = rect.length * rect.width;
  printf("The area of the rectanlge is %.2f\n", area);

  return 0;
}
