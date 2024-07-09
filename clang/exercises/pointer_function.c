/*    pointer_function.c
 *
 *    an example of a how to declare, define, and call a function pointer
 */

#include <stdio.h> // printf


/******************************
 *
 *          function
 *
 ******************************/
int my_func (int i) {
  printf("Got into function `my_func` with %d\n", i);

  return 0;
}


/******************************
 *
 *          driver, including function pointer
 *
 ******************************/
int main (void) {

  int (*func)(int);
/* function pointer declaration
 *
 *^^^                           the function's         return type
 *    ^^^^^^^                   the function pointer's name
 *           ^^^^^              the function's         parameter types, comma-separated
 */

  func = my_func;
/* function pointer definition
 *
 *^^^^            function pointer name
 *       ^^^^^^^  function         name
 */

  func(7);

  return 0;
}