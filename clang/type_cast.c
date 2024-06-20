/*    typecast.c
 */

#include <stdio.h>

int main (void) {
  short int   si = 9;
  long  int   li = 1234567890L;
  float        f = 3.14;
  double       d = 1234567890.1234567;
  char         c = 'a';
  char      *ptr = &si;

  printf("short int %d %f %p\n",    (int)si,  (float)si, (char *)si);
  printf("long  int %d %f %p\n",    (int)li,  (float)li, (char *)li);
  printf("float     %d %f (ERR)\n", (int)f,   (float)f);
  printf("double    %d %f (ERR)\n", (int)d,   (float)d);
  printf("char      %d %f %p\n",    (int)c,   (float)c,  (char *)c);
  printf("ptr       %d (ERR) %p\n", (int)ptr, (char *)ptr);

  return 0;
}
