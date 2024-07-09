/*    fileio_lib.c
 *
 *    an example of library-style file I/O
 *
 */

#include <errno.h>  // errno
#include <stdio.h>  // fclose, feof, fflush, fgets, fopen, fprintf, fputs, fscanf, printf
#include <string.h> // strerror


int show_fopen (void) {
  int x, y, z;
  FILE *file;
  char *filename = "fopen.dat";
  char str[128];
  
  file = fopen(filename, "r+"); // open for reading and writing
  if (file == NULL) {
    fprintf(stderr, "fopen() failed, error=%s\n", strerror(errno));
    return -1;
  }

  while (!feof(file)) {
    if (fscanf(file, "%d %d %d\n", &x, &y, &z) == 3)
      printf("Read coordinates [%d,%d,%d]\n", x, y, z);

    if (!feof(file)) {
      fgets(str, 128, file);
      if (fgets(str, 128, file) != NULL)
        printf("Read lines [%s]\n", str);
    }
  }

  x = 21;
  y = 34;
  z = 98;

  fprintf(file, "%d %d %d\n", x, y, z);
  printf( "Wrote %d %d %d\n", x, y, z);
  if (fputs(str, file) >= 0)
    printf("Wrote line [%s]\n", str);
  fflush(file);
  fclose(file);

  return 0;
}


/******************************
 *
 *          driver
 *
 ******************************/
int main (void) {
  show_fopen();

  return 0;
}