/*    fileio_sys.c
 *
 *    an example of system call-style file I/O
 *    view the contents of file `open.dat` via `od -x -N 256 open.dat`
 */

#include <errno.h>    // errno
#include <fcntl.h>    // close, O_CREAT, O_EXCL, O_WRONLY, open
#include <stdio.h>    // fprintf, stderr
#include <strings.h>  // strerror
#include <sys/stat.h> // mode_t
#include <unistd.h>   // read, write


int show_open (void) {
  char *filename = "open.dat";
  int vals[1000] = { [0 ... 999] = 0xff }, vals2[1000];

  int    flag = O_WRONLY | O_CREAT | O_EXCL;  // attempt to create a new file regardless of whether it already exists
  mode_t mode = S_IRUSR  | S_IWUSR | S_IRGRP;
  /*            ^^^^^^^                       user  read
   *                       ^^^^^^^            user  write
   *                                 ^^^^^^^  group read
   */

  int fd = open(filename, flag, mode);
  if (fd == -1) {
    fprintf(stderr, "open() failed, error=%s\n", strerror(errno));
    return -1;
  }

  // write the array `vals` to the file `open.dat`
  if (write(fd, (char *)vals, sizeof(vals)) != sizeof(vals)) {
    fprintf(stderr, "write() failed, error=%s\n", strerror(errno));
    return -1;
  }

  close(fd); fd = -1;

  // setup the file for reading
  flag = O_RDONLY;
  fd   = open(filename, flag, 0);
  if (fd == -1) {
    fprintf(stderr, "open() failed, error=%s\n", strerror(errno));
    return -1;
  }

  // read the array `vals` from the file `open.dat`
  if (read(fd, (char *)vals2, sizeof(vals2)) != sizeof(vals2)) {
    fprintf(stderr, "read() failed, error=%s\n", strerror(errno));
    return -1;
  }

  close(fd); fd = -1;

  return 0;
}


/******************************
 *
 *          driver
 *
 ******************************/
int main (void) {
  show_open();

  return 0;
}