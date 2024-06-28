# Iteration 2

Your internship is going great. You have gained experience with C programming, you have experienced your first segmentation faults, and you've come out on top. You are brimming with confidence and ready to handle your next challenge.

## Tasks

### Task 1

Your next task is to implement write functionality for mdadm and then thoroughly test your implementation. Specifically, you will implement the following function:

```c
int mdadm_write (uint32_t start_addr, uint32_t write_len, const uint8_t *write_buf)
```

Let's take a closer look at this function:

```c
// write `write_len` bytes from the user-supplied buffer `write_buf` to the storage system starting at address `start_addr`
int mdadm_write (uint32_t start_addr, uint32_t write_len, const uint8_t *write_buf) {
  /*             ^^^^^^^^^^^^^^^^^^^                                                32-bit unsigned int
   *                                  ^^^^^^^^^^^^^^^^^^                            32-bit unsigned int
   *                                                      ^^^^^                     `write_buf` is an in-parameter, meaning that it is read-only
   *                                                      ^^^^^^^^^^^^^^^^^^^^^^^^  pointer to 8-bit unsigned int
   *
   * YOUR IMPLEMENTATION
   *
   * writing to an out-of-bounds address must fail
   * a write larger than 1,024 bytes     must fail (i.e., LEN <= 1024)
   * there are some other requirements as well
   * 
   * this function returns `write_len` on success and -1 on failure
   */
  if (...) return -1;
  if (...) return -1;
  ...
  return write_len;
}
```

Once this function is implemented, the basic read and write functionality of the storage system will be in place!

### Task 2

The cryptocurrency startup that you are interning at is also concerned about the security of their storage system. To ensure that data is written by the correct people at the correct times, you will implement the following functions, which will enable and disable the write permission of the storage system.

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

## JBOD API

The following commands are provided in addition to the commands of the first iteration:

command | description | example
-|-|-
`JBOD_WRITE_PERMISSION` | Sets the write permission to $1$: write enabled. When the command field of `op` is set to this command, the JBOD driver ignores all other fields. Parameter `block` may be set to `NULL`. | `jbod_operation(JBOD_WRITE_PERMISSION, NULL)`
`JBOD_REVOKE_WRITE_PERMISSION` | Sets the write permission to $-1$: write disabled. When the command field of `op` is set to this command, the JBOD driver ignores all other fields. Parameter `block` may be set to `NULL`. | `jbod_operation(JBOD_REVOKE_WRITE_PERMISSION, NULL)`

## Testing

Running the following commands without issue indicates that the implementation is sufficient.

```bash
make clean
make

./tester                                                                 # should pass all 18 unit tests
./tester -w traces/simple-input                                          # should produce cryptographic checksum
./tester -w traces/linear-input                                          # should produce cryptographic checksum
./tester -w traces/random-input                                          # should produce cryptographic checksum

diff -u <(./tester -w traces/simple-input) traces/simple-expected-output # should produce no output
diff -u <(./tester -w traces/linear-input) traces/linear-expected-output # should produce no output
diff -u <(./tester -w traces/random-input) traces/random-expected-output # should produce no output
```

The mdadm implementation is a layer just above the JBOD. The purpose of mdadm is to unify multiple disks under one storage system with a single address space. An application built on top of mdadm will issue a sequence of commands, such as the following:

```txt
MOUNT
WRITE_PERMISSION
...a sequence of READS and WRITES, issued at arbitrary addresses with arbitrary payloads
UNMOUNT
```

In addition to the usual suite of unit tests, there are three trace files which contain a list of commands a system built on top of the mdadm implementation might issue. The unit test suite now includes functionality to replay the trace files; in particular, the suite of unit tests now has two modes of operation.

Without any arguments, the unit test utility will run its suite of unit tests:

```c
./tester
```

With the path name argument `-w`, the unit test utility expects the path name to one of the three bundled trace files. The three possibilities are then the following:

```bash
./tester -w traces/simple-input
./tester -w traces/linear-input
./tester -w traces/random-input
```

If we take a peak at one of the trace files.

```txt
MOUNT
WRITE_PERMIT
WRITE 0 256 0        write to   address       0, for 256 B, each byte is 0
READ 1006848 256 0   read  from address 1006848, for 256 B, ignore last arg
```