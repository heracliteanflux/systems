# Multiple Disk and Device Administration - Linear Device

Today is the first day of your internship at a cryptocurrency startup. The marketing team has decided that they want to differentiate their product by emphasizing security. The startup has just received a shipment of 16 military-grade nuclear bomb-proof hard disks which will replace the existing commercial-grade hard disks for the purposes of storing critical user data in the form of cryptocurrency wallets. The company that manufactured the disks focuses on physical security but didn't invest in the software, and provided their product as just a bunch of disks (JBOD). JBOD is a storage architecture consisting of numerous disks inside a single enclosure. The user manual that came with the product specifies the following.

"Thank you for purchasing our military-grade, nuclear bomb-proof hard disk product built with the same patented technology that's used by NASA. Each drive consists of 256 storage blocks where a storage block consists of 256 bytes. Thus each disk contains 65,536 bytes of storage.

$$
\begin{align}
 16 \\,\\,\text{disks}\\,\\, \times 
\\underbrace{
256 \\,\\,\text{blocks per disk}\\,\\, \times 
256 \\,\\,\text{B per block}
}_{65,536 \\,\\,\text{B per disk}}
&= 1,048,576 \\,\\,\text{B} \\
 \\underbrace{16}_{2^4} \\,\\,\text{disks}\\,\\, \times \\underbrace{64}_{2^6} \\,\\,\\underbrace{\text{KB}}_{2^{10}} \text{per disk} &= 1 \\,\\,\\underbrace{\text{MB}}_{2^20} \\
\end  {align}
$$

The interface to the JBOD is a device driver with the function `jbod_operation` which returns $0$ on success and $-1$ on failure. It accepts two parameters: an operation via parameter `op` the format of which is described below and a pointer to a buffer via parameter `block`.

```c
int jbod_operation (uint32_t op, uint8_t *block) {
  //                ^^^^^^^^^^^                             32-bit unsigned int
  //                             ^^^^^^^^^^^^^^   pointer to 8-bit unsigned int
  if (success) return  0;
  else         return -1;
}
```

#### The format of parameter `op`

$$\\underbrace{\\overset{31}{0}000 \\, 0000 \\, 0000 \\, 0\\overset{18}{0}}\_{\\text{reserved}} \\,
  \\underbrace{\\overset{17}{0}0 \\, 0000 \\, 0\\overset{10}{0}}\_{\\text{block}} \\,
  \\underbrace{\\overset{ 9}{0}0 \\, 0\\overset{6}{0}}\_{\\text{disk}} \\,
  \\underbrace{\\overset{ 5}{0}0 \\, 000\\overset{0}{0}}\_{\\text{command}}$$

bits | width | field | description
-|-|-|-
  0-5 |  6 | command  | the command to be executed by the JBOD
  6-9 |  4 | disk ID  | 
10-17 |  8 | block ID |
18-31 | 14 | reserved | unused for now

#### The command field

The command field is one of the following commands. (They are declared as type `enum` in header file `jbod.h`).

command | description | example
-|-|-
`JBOD_MOUNT`         | Mounts all disks in the JBOD and prepares them to receive further instruction. This command must be called before any other commands or else they will fail. When the command field of `op` is set to this command, the JBOD driver ignores all other fields. Parameter `block` may be set to `NULL`. | `jbod_operation(JBOD_MOUNT, NULL)`
`JBOD_UNMOUNT`       | Unmounts all disks in the JBOD. Any command other than the mount command called after this command will fail. When the command field of `op` is set to this command, the JBOD driver ignores all other fields. Parameter `block` may be set to `NULL`. | `jbod_operation(JBOD_UNMOUNT, NULL)`
`JBOD_SEEK_TO_DISK`  | Seeks to block 0 of a specific disk. Internally, JBOD maintains an I/O position which takes the form of a tuple $(\\texttt{current\\_disk\\_ID}, \\texttt{current\\_block\\_ID})$ which determines where the next operation will occur. In particular, this command seeks to the beginning of a disk specified by the disk ID field of `op` by modifying the I/O position tuple $(\\texttt{current\\_disk\\_ID}\\,\\, = \\texttt{disk\\_ID}, \\texttt{current\\_block\\_ID} \\,\\, = 0)$. When the command field of `op` is set to this command, the JBOD driver ignores the block ID field. Parameter `block` may be set to `NULL`. | `jbod_operation(JBOD_SEEK_TO_DISK, NULL)`
`JBOD_SEEK_TO_BLOCK` | Seeks to a specific block of the current disk. In particular, this command seeks to the beginning of a blcok of the current disk which is specified by the block ID field of `op` by modifying the I/O position tuple $(\\texttt{current\\_disk\\_ID}, \\texttt{current\\_block\\_ID} \\,\\, = \\texttt{block\\_ID})$. When the command field of `op` is set to this command, the JBOD driver ignores the disk ID field. Parameter `block` may be set to `NULL`. | `jbod_operation(JBOD_SEEK_TO_BLOCK, NULL)`
`JBOD_READ_BLOCK`    | Reads the block in the current I/O position into the buffer specified by parameter `block`. After this operation is complete, $\\texttt{current\\_block\\_ID}$ is incremented by $1$ and so the next operation will occur on the next block of the current disk. When the command field of `op` is set to this command, the JBOD driver ignores all other fields. | `jbod_operation(JBOD_READ_BLOCK, read_buffer)`
`JBOD_WRITE_BLOCK`   | Writes the data in buffer `block` into the block in the current I/O position. After this operation is complete, $\\texttt{current\\_block\\_ID}$ is incremented by $1$ and so the next operation will occur on the next block of the current disk. When the command field of `op` is set to this command, the JBOD driver ignores all other fields. | `jbod_operation(JBOD_WRITE_BLOCK, write_buffer)`

Thank you for your purchase!"

#### The implementation

After you finish your onboarding session and enjoyed a free lunch with your new colleagues, you receive the following email from the team manager.

"Welcome to the team! Here's your first task. You will work on integrating the JBOD into our existing storage system. For the next week or so, you will implement one of the functionalities of the `mdadm` Linux utility, which is an acronym for "multiple disk and device administration": a tool for doing cool tricks with multiple disks! In particular, you will implement a linear device. A linear device makes multiple disks appear as one large disk to the operating system. In our case, we will make $16$ $64 \\,\\,\\text{KB}$-disks appear as one $4 \\,\\,\\text{MB}$-disk to the operating system.

Described below is the specific functionality that must be implemented.

File `jbod.h`:

```h
// enter the correct values for the following macros
#define DISK      //     16 disks
#define BLCK_SIZE //    256 B per block
#define BLCK_DISK //    256 blocks per disk
#define DISK_SIZE // 65,536 B per disk
```

File `mdadm.c`:

```c
// mount the linear device
int mdadm_mount   (void) {
  /* YOUR IMPLEMENTATION
   *
   * calling this function a second time without calling function `mdadm_unmount` in the interim must fail
   * this function returns 1 on success and -1 on failure
   */
  if (jbod_operation(...) == 0) return  1; // success
  else                          return -1; // failure --> jbod_operation == -1, or another non-zero value
}

// unmount the linear device
int mdadm_unmount (void) {
  /* YOUR IMPLEMENTATION
   *
   * calling this function a second time without calling function `mdadm_mount` in the interim must fail
   * this function returns 1 on success and -1 on failure
   */
  if (jbod_operation(...) == 0) return  1; // success
  else                          return -1; // failure --> jbod_operation == -1, or another non-zero value
}

// read LEN bytes into BUF starting at address ADDR
int mdadm_read (uint32_t addr, uint32_t LEN, uint8_t *BUF) {
  /*            ^^^^^^^^^^^^^                                         32-bit unsigned int
   *                           ^^^^^^^^^^^^                           32-bit unsigned int
   *                                         ^^^^^^^^^^^^   pointer to 8-bit unsigned int
   *
   * YOUR IMPLEMENTATION
   *
   * reading from an out-of-bounds address must fail
   * a read larger than 1,024 bytes should fail (i.e., LEN <= 1024)
   * there are some other requirements as well
   * this function returns LEN on success and -1 on failure
   */
  if (...) return -1;
  if (...) return -1;
  ...
  return LEN;
}
```

Good luck!"

You are ready to make an impact in the company! You spend the afternoon with your mentor who goes through the directory structure and the development procedure with you.

```txt
  jbod.h    JBOD interface, the constants defined here are used in the implementation
  jbod.o    the object file containing the JBOD driver
 mdadm.h    the header file that lists the functions that are to be implemented
 mdadm.c    the implementation of the mdadm functions
tester.h
tester.c    unit tests for the functions that are to be implemented; this file compiles into the executable `tester` which when run will determine whether the implementation is satisfactory
  util.h
  util.c    utility functions that JBOD (and unit tests) relies on
Makefile    used by utility `make` to compile and build the executable `tester`
```

Recommended workflow:
1. update file `jbod.h` with the appropriate macro values
2. edit the name of file `jbod.o` according to the architecture of the machine being used to test the implementation: in particular, if you are using Apple Silicon (M1/2/3) then remove file `jbod.o` and rename file `jbod-m1.o` to `jbod.o`.
3. Repeat the following until all unit tests are passed:
    1. implement functionality in file `mdadm.c`
    2. `make clean`
    3. `make`
    4. `./tester`
    5. commit and push

  It may be helpful to check the return value of function `jbod_operation` to determine whether an operation was successful. Remember that if the JBOD isn't initially mounted then all other read operations will fail.