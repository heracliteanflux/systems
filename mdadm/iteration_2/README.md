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
  /*    YOUR IMPLEMENTATION
   */
}

// tell the storage system that writing is now not allowed
int mdadm_revoke_write_permission (void) {
  /*    YOUR IMPLEMENTATION
   */
}
```

Write permission must be enabled prior to writing to the storage system, and the API must check whether writing permission is already enabled prior to each write operation.

The following commands are provided:

command | description | example
-|-|-
`JBOD_WRITE_PERMISSION` | Sets the write permission to $1$: write enabled. When the command field of `op` is set to this command, the JBOD driver ignores all other fields. Parameter `block` may be set to `NULL`. | `jbod_operation(JBOD_WRITE_PERMISSION, NULL)`
`JBOD_REVOKE_WRITE_PERMISSION` | Sets the write permission to $-1$: write disabled. When the command field of `op` is set to this command, the JBOD driver ignores all other fields. Parameter `block` may be set to `NULL`. | `jbod_operation(JBOD_REVOKE_WRITE_PERMISSION, NULL)`

The mdadm implementation is a layer just above the JBOD. The purpose of mdadm is to unify multiple disks under one storage system with a single address space. An application built on top of mdadm will issue a sequence of commands like the following:

```txt
MOUNT
WRITE_PERMISSION
a sequence of WRITES and READS issued at arbitrary addresses with arbitrary payloads
UNMOUNT
```

In addition to the unit tests there are several trace files which contain the list of commands a system built on top of the mdadm implementation might issue. The unit test suite now includes functionality to replay the trace files; in particular, the suite of unit tests now has two modes of operation. Without any arguments, the utility will run the suite of unit tests:

```c
./tester
```

With the path name argument `-w` the test utility expects a path name that points to a trace file.

```c
./tester -w traces/simple-input   // simple-input, linear-input, random-input
```

```txt
MOUNT
WRITE_PERMIT
WRITE 0 256 0        write to   address       0, for 256 B, each byte is 0
READ 1006848 256 0   read  from address 1006848, for 256 B, ignore last arg
```