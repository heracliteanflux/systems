mdadm linear device

Today is the first day of your internship at a cryptocurrency startup. The marketing team has decided that they want to differentiate their product by emphasizing security. The startup has just received a shipment of 16 military-grade nuclear bomb-proof hard disks which will replace the existing commercial-grade hard disks for the purposes of storing critical user data in the form of cryptocurrency wallets. The company that manufactured the disks focuses on physical security but didn't invest in the software, and provided their product as just a bunch of disks (JBOD). JBOD is a storage architecture consisting of numerous disks inside a single enclosure. The user manual that came with the product specifies the following.

"Thank you for purchasing our military-grade, nuclear bomb-proof hard disk product built with the same patented technology that's used by NASA. Each drive consists of 256 storage blocks where a storage block consists of 256 bytes. Thus each disk contains 65,536 bytes of storage.

$16 \\,\\,\text{disks}\\,\\, \times 256 \\,\\,\text{blocks per disk}\\,\\, \times 256 \\,\\,\text{B per block} = 1,048,576 \\,\\,\text{B}$

The interface to the JBOD is a device driver containing a function with the following signature:"

```c
int jbod_operation (uint32_t op, uint8_t *block)
```