/*    array_2d.c
 *
 *    // a M row x N col array of (M x N) type --> index 0..(M x N - 1)
 *    type arr[M][N];
 * 
 *    // elem (m x N + n)
 *    arr[m][n];
 *
 */

#include <stdio.h>   // printf

int main () {
  // 2 row x 3 col array of  6 double --> index 0..5
  double grid[2][3];

  // 3 row x 5 col array of 15 int    --> index 0..14
  int matrix[3][5] = {
    {0, 1, 2, 3, 4},
    {0, 2, 4, 6, 8},
    {1, 3, 5, 7, 9}
  };

  // replace the 3rd elem of array `grid` with the last elem of array `matrix`
  //   and cast its type from int to double
  //
  //   grid   (0 x 3 + 2) =  2, third elem out of  6
  //   matrix (2 x 5 + 4) = 14, last  elem out of 14
  grid[0][2] = (double) matrix[2][4];

  printf("grid\n");
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 3; j++) {
      printf("%.2lf ", grid[i][j]);
    }
    printf("\n");
  }
  /*   output
   *
   *   0.00 0.00 9.00 
   *   0.00 0.00 0.00
   */

  return 0;
}