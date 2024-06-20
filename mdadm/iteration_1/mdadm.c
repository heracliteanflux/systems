/*    mdadm.c    Multiple Disk and Device Administration
 */

#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "mdadm.h"
#include "jbod.h"

const int DISK          = JBOD_NUM_DISKS;           //        16 disk
const int BLCK_PER_DISK = JBOD_NUM_BLOCKS_PER_DISK; //       256 blck      per disk
const int BLCK_SIZE     = JBOD_BLOCK_SIZE;          //       256 B         per blck
const int DISK_SIZE     = JBOD_DISK_SIZE;           //    65,536 B (64 KB) per disk
const int JBOD_SIZE     = DISK_SIZE * DISK;         // 1,048,576 B ( 1 MB) per jbod
const int MAX_RDLEN     = BLCK_SIZE * 4;            //     1,024 B ( 1 KB)
const int IGND          = 0;
      int is_mounted    = 0;

uint32_t op (uint32_t rsvd, uint32_t blck, uint32_t disk, uint32_t cmnd) {
  return              rsvd << 18   | blck << 10   | disk <<  6   | cmnd;
  //        xxxx xxxx xxxx xxxx xx | xx xxxx xx   | xx xx        | xx xxxx
}

int mdadm_mount (void) {
  uint32_t opcode = op(IGND, IGND, IGND,   JBOD_MOUNT);
  int jbod_result = jbod_operation(opcode, NULL);
  if (jbod_result == 0) { is_mounted = 1; return  1; }
  else                  {                 return -1; }
}

int mdadm_unmount (void) {
  uint32_t opcode = op(IGND, IGND, IGND, JBOD_UNMOUNT);
  int jbod_result = jbod_operation(opcode, NULL);
  if (jbod_result == 0) { is_mounted = 0; return  1; }
  else                  {                 return -1; }
}

void addr (uint32_t *start_addr, uint32_t *disk, uint32_t *blck, uint32_t *ofst) {
  *disk = *start_addr / DISK_SIZE;
  *blck = *start_addr % DISK_SIZE / BLCK_SIZE;
  *ofst = *start_addr % DISK_SIZE % BLCK_SIZE;
}

int mdadm_read(uint32_t start_addr, uint32_t read_len, uint8_t *read_buf)  {
  uint32_t disk;
  uint32_t blck;
  uint32_t ofst;

  // input validation
  if (!is_mounted)                                  return -1;   // JBOD must be mounted
  if (!(0 <= start_addr && start_addr < JBOD_SIZE)) return -1;   // 0 <= start_addr < 1,048,576 (2^20)
  if (!(0 <= read_len   && read_len   < MAX_RDLEN)) return -1;   // 0 <= read_len   <     1,024 (2^10)
  if (!(     start_addr  + read_len  <= JBOD_SIZE)) return -1;   // start_addr + read_len <= 1,048,576
  if (read_buf == NULL && read_len > 0)             return -1;

  // initialization - seek to correct disk and block of `start_addr`
  addr(&start_addr, &disk, &blck, &ofst);
  assert(jbod_operation(op(IGND, IGND, disk, JBOD_SEEK_TO_DISK),  NULL) == 0);
  assert(jbod_operation(op(IGND, blck, IGND, JBOD_SEEK_TO_BLOCK), NULL) == 0);

  // read
  int bytes_to_be_read = read_len;
  int bytes_read       = 0;
  while (bytes_to_be_read > 0) {                                                                     // `read_len` must be at least 1
    int chunk = bytes_to_be_read >= (BLCK_SIZE - ofst) ? BLCK_SIZE - ofst : bytes_to_be_read - ofst; // how many B to read? 256 - (0..255) = 1..256

    // read operation
    uint8_t buf[BLCK_SIZE];                                                  // 256-B buffer
    assert(jbod_operation(op(IGND, IGND, IGND, JBOD_READ_BLOCK), buf) == 0); // read entire block into `buf`
    memcpy(read_buf, &buf[ofst], chunk);                                     // read chunk of `buf` into `read_buf`

    // post read operation
    read_buf         += chunk;              // update pointer `read_buf`
    bytes_to_be_read -= chunk;              // update        the number of bytes to be read
    bytes_read       += chunk;              // keep track of the number of bytes       read
    start_addr       += chunk;              // recompute location in JBOD
    addr(&start_addr, &disk, &blck, &ofst); // recompute location in JBOD
    if (blck == 0) {                        // if the updated blck value is 0 then seek to the next disk
      assert(jbod_operation(op(IGND, IGND, disk, JBOD_SEEK_TO_DISK), NULL) == 0);
    }
  }

  // successful read
  assert(bytes_read == read_len);
  return bytes_read;
}