mdadm linear device

Today is the first day of your internship at a cryptocurrency startup. The marketing team has decided that they want to differentiate their product by emphasizing security. The startup has just received a shipment of 16 military-grade nuclear bomb-proof hard disks which will replace the existing commercial-grade hard disks for the purposes of storing critical user data in the form of cryptocurrency wallets. The company that manufactured the disks focuses on physical security but didn't invest in the software, and provided their product as just a bunch of disks (JBOD). JBOD is a storage architecture consisting of numerous disks inside a single enclosure. The user manual that came with the product specifies the following.

"Thank you for purchasing our military-grade, nuclear bomb-proof hard disk product built with the same patented technology that's used by NASA. Each drive consists of 256 storage blocks where a storage block consists of 256 bytes. Thus each disk contains 65,536 bytes of storage.

$16 \\,\\,\text{disks}\\,\\, \times 256 \\,\\,\text{blocks per disk}\\,\\, \times 256 \\,\\,\text{B per block} = 1,048,576 \\,\\,\text{B}$

The interface to the JBOD is a device driver with the function

```c
int jbod_operation (uint32_t op, uint8_t *block)
```

which returns `0` on success and `-1` on failure. It accepts two parameters: an operation via parameter `op` the format of which is described below and a pointer to a buffer via parameter `block`.

$
\\underbrace{0000 \\, 0000 \\, 0000 \\, 0000 \\, 0000 \\, 00}\_{\\text{reserved}}
\\underbrace{00 \\, 0000 \\, 00}\_{\\text{block}}
\\underbrace{00 \\, 00}\_{\\text{disk}}
\\underbrace{00 \\, 0000}\_{\\text{command}}
$