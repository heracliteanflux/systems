/*    union_2d_3d_point.c
 *
 *    Define a union called `Point` which can store either a 2D point or a 3D point.
 *    Prompt the user to choose between the type of point.
 *    Based on their choice, store and display the point.
 */

#include <stdio.h>

union Point {
  struct { int x, y;    } d2;
  struct { int x, y, z; } d3;
};

int main () {
  union Point point;
  int         choice;

  printf("2d point or 3d point?\nEnter `2` or `3`: ");
  scanf("%d", &choice);

       if (choice == 2) {
    printf("x coord: ");
    scanf("%d", &point.d2.x);

    printf("y coord: ");
    scanf("%d", &point.d2.y);

    printf("The stored 2D point has coordinates (%d, %d)\n", point.d2.x, point.d2.y);
  }
  else if (choice == 3) {
    printf("x coord: ");
    scanf("%d", &point.d3.x);

    printf("y coord: ");
    scanf("%d", &point.d3.y);

    printf("z coord: ");
    scanf("%d", &point.d3.z);

    printf("The stored 3D point has coordinates (%d, %d, %d)\n", point.d3.x, point.d3.y, point.d3.z);
  }
  else {
    printf("Invalid choice! Exiting...\n");
  }

  return 0;
}