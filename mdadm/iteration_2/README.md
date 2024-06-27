Your internship is going great. You have gained experience with C programming, you have experienced your first segmentation faults, and you've come out on top. You are brimming with confidence and ready to handle your next challenge. Your next job is to implement write functionality for mdadm and then thoroughly test your implementation. Specifically, you will implement the following function:

```c
// write `write_len` bytes from the user-supplied buffer `write_buf` to the storage system starting at address `start_addr`
int mdadm_write (uint32_t start_addr, uint32_t write_len, const uint8_t write_buf) {
  /*             ^^^^^^^^^^^^^^^^^^^                                               32-bit unsigned int
   *                                  ^^^^^^^^^^^^^^^^^^                           32-bit unsigned int
   *                                                      ^^^^^                    `write_buf` is an in-parameter, meaning that it is read-only
   *                                                      ^^^^^^^^^^^^^^^^^^^^^^^  pointer to 8-bit unsigned int
   *
   * YOUR IMPLEMENTATION
   *
   * writing to an out-of-bounds address must fail
   * a write larger than 1,024 bytes should fail (i.e., LEN <= 1024)
   * there are some other requirements as well
   * this function returns `write_len` on success and -1 on failure
   */
  if (...) return -1;
  if (...) return -1;
  ...
  return write_len;
}
```

Once this function is implemented the basic functionality of the storage system will be in place.

The cryptocurrency startup that you are interning at is concerned about the security of their storage systems. To ensure that data is written by the correct people at the correct times, you are to implement the following functions, which will set the write permissions of the storage system.

```c
// tell the storage system that writing is now allowed
int mdadm_write_permission (void) {

}

// tell the storage system that writing is now not allowed
int mdadm_revoke_write_permission (void) {

}
```

Write permission must be enabled prior to writing to the storage system, and the API must check whether writing permission is already enabled prior to each write operation.

The following commands are provided:

```c
JBOD_WRITE_PERMISSION   // set write permission to 1, allowed

```