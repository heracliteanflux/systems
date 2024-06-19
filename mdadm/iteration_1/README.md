mdadm linear device

Today is the first day of your internship at a cryptocurrency startup. The marketing team has decided that they want to differentiate their product by emphasizing security. The startup has just received a shipment of 16 military-grade nuclear bomb-proof hard disks which will replace the existing commercial-grade hard disks for the purposes of storing critical user data in the form of cryptocurrency wallets. The company that manufactured the disks focuses on physical security but didn't invest in the software, and provided their product as just a bunch of disks (JBOD). JBOD is a storage architecture consisting of numerous disks inside a single enclosure. The user manual that came with the product specifies the following.

"Thank you for purchasing our military-grade, nuclear bomb-proof hard disk product built with the same patented technology that's used by NASA. Each drive consists of 256 storage blocks where a storage block consists of 256 bytes. Thus each disk contains 65,536 bytes of storage.

$16 \\,\\,\text{disks}\\,\\, \times 256 \\,\\,\text{blocks per disk}\\,\\, \times 256 \\,\\,\text{B per block} = 1,048,576 \\,\\,\text{B}$

The interface to the JBOD is a device driver with the function

```c
int jbod_operation (uint32_t op, uint8_t *block)
```

which returns $0$ on success and $-1$ on failure. It accepts two parameters: an operation via parameter `op` the format of which is described below and a pointer to a buffer via parameter `block`.

$\\underbrace{0000 \\, 0000 \\, 0000 \\, 0000 \\, 0000 \\, 00}\_{\\text{reserved}}
\\underbrace{00 \\, 0000 \\, 00}\_{\\text{block}}
\\underbrace{00 \\, 00}\_{\\text{disk}}
\\underbrace{00 \\, 0000}\_{\\text{command}}$

bits | width | field | description
-|-|-|-
  0-5 |  6 | command  | the command to be executed by the JBOD
  6-9 |  4 | disk ID  | 
10-17 |  8 | block ID |
18-31 | 14 | reserved | unused for now

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

After you finish your onboarding session and enjoyed a free lunch with your new colleagues, you receive the following email from the team manager.