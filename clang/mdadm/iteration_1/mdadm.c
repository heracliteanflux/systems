/*    mdadm.c    Multiple Disk and Device Administration
 *
 *    Iteration 1
 */

#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "mdadm.h"
#include "jbod.h"

//        my names for    jbod.h macro names
//        =============   =========================
const int DISK          = JBOD_NUM_DISKS;           //        16 disk
const int BLCK_PER_DISK = JBOD_NUM_BLOCKS_PER_DISK; //       256 blck      per disk
const int BLCK_SIZE     = JBOD_BLOCK_SIZE;          //       256 B         per blck
const int DISK_SIZE     = JBOD_DISK_SIZE;           //    65,536 B (64 KB) per disk
const int JBOD_SIZE     = DISK_SIZE * DISK;         // 1,048,576 B ( 1 MB) per jbod
const int MAX_RDLEN     = BLCK_SIZE * 4;            //     1,024 B ( 1 KB)
const int IGND          = 0;                        // mask
      int is_mounted    = 0;                        //    unmounted = 0,  mounted = 1


/********************************************************************************
 *
 *                    JBOD Auxiliary
 *
 ********************************************************************************/


/* construct a 32-bit operation
 *
 * return
 *   32-bit operation
 */
uint32_t op (uint32_t rsvd, uint32_t blck, uint32_t disk, uint32_t cmnd) {
  return              rsvd << 18   | blck << 10   | disk <<  6   | cmnd;
  //        xxxx xxxx xxxx xxxx xx | xx xxxx xx   | xx xx        | xx xxxx
}


// compute location in JBOD in terms of disk, blck, and ofst from beginning of block
void addr (uint32_t *start_addr, uint32_t *disk, uint32_t *blck, uint32_t *ofst) {
  *disk = *start_addr / DISK_SIZE;             assert(0 <= *disk && *disk < DISK_SIZE);  // 0..(2^20 - 1) / 2^16 = 0..(2^4 - 1) --> a number between 0 and  15
  *blck = *start_addr % DISK_SIZE / BLCK_SIZE; assert(0 <= *blck && *blck < BLCK_SIZE);  // 0..(2^16 - 1) /  2^8 = 0..(2^8 - 1) --> a number between 0 and 255
  *ofst = *start_addr % DISK_SIZE % BLCK_SIZE; assert(0 <= *ofst && *ofst < BLCK_SIZE);  // 0..( 2^8 - 1)                       --> a number between 0 and 255
}


/* input validation for read and write
 *
 * return
 *   -1 on failure
 *    1 on success
 */
int rdwt_validate (uint32_t start_addr, uint32_t rdwt_len, const uint8_t *rdwt_buf) {
  if (!is_mounted)                                   return -1;   // JBOD must be mounted
  if (!(0 <= start_addr && start_addr <  JBOD_SIZE)) return -1;   // 0 <= start_addr       <  1,048,576 (2^20)
  if (!(0 <= rdwt_len   && rdwt_len   <= MAX_RDLEN)) return -1;   // 0 <= rdwt_len         <      1,024 (2^10)
  if (!(     start_addr  + rdwt_len   <= JBOD_SIZE)) return -1;   // start_addr + rdwt_len <= 1,048,576 (2^20)
  if (rdwt_buf == NULL  && rdwt_len   >  0)          return -1;

  return 1;
}


/********************************************************************************
 *
 *                    JBOD
 *
 ********************************************************************************/


/* mount the linear device
 *
 * return
 *   -1 on failure
 *    1 on succuss
 */
int mdadm_mount (void) {
  if                     (is_mounted == 1) return -1;   // failure!   --> if JBOD is already   mounted then fail this attempt to   mount
  uint32_t opcode = op(IGND, IGND, IGND,   JBOD_MOUNT); // otherwise, proceed with   mount
  int jbod_result = jbod_operation(opcode, NULL);
  if (jbod_result == 0) { is_mounted  = 1; return  1; } // success!   --> JBOD successfully   mounted
  else                                     return -1;   // failure!   --> JBOD could not   mount for some reason
}
// int mdadm_mount (void) {
//   if                                                                (is_mounted == 1) return -1;
//   if (jbod_operation(op(IGND, IGND, IGND, JBOD_MOUNT), NULL) == 0) { is_mounted  = 1; return  1; }
//   else                                                                                return -1;
// }


/* unmount the linear device
 *
 * return
 *   -1 on failure
 *    1 on succuss
 */
int mdadm_unmount (void) {
  if                     (is_mounted == 0) return -1;   // failure!   --> if JBOD is already unmounted then fail this attempt to unmount
  uint32_t opcode = op(IGND, IGND, IGND, JBOD_UNMOUNT); // otherwise, proceed with unmount
  int jbod_result = jbod_operation(opcode, NULL);
  if (jbod_result == 0) { is_mounted  = 0; return  1; } // success!   --> JBOD successfully unmounted
  else                                     return -1;   // failure!   --> JBOD could not unmount for some reason
}


/* read `read_len` bytes into `read_buf` starting at address `start_addr`
 *
 * return
 *   -1              on failure
 *    num bytes read on succuss
 */
int mdadm_read(uint32_t start_addr, uint32_t read_len, uint8_t *read_buf)  {
  uint32_t disk, // will hold a value 0.. 15 + 1
           blck, //                   0..255
           ofst; //                   0..255

  // input validation
  if (rdwt_validate(start_addr, read_len, (const uint8_t *)read_buf) == -1) return -1;

  // read operation
  int    bytes_read = 0;
  while (bytes_read < read_len) { // `read_len` must be at least 1
    uint8_t buf[BLCK_SIZE];       // holds the full 256 B of the current blck

    // compute location in JBOD in terms of disk, blck, and ofst from beginning of blck
    addr(&start_addr, &disk, &blck, &ofst);

    // how many B to read?               256       - (0..255) = 1..256
    int chunk = read_len - bytes_read >= BLCK_SIZE - ofst
              ?                          BLCK_SIZE - ofst
              : read_len - bytes_read;

    // seek to correct disk and block of `start_addr`
    assert(jbod_operation(op(IGND, IGND, disk, JBOD_SEEK_TO_DISK),  NULL) == 0);
    assert(jbod_operation(op(IGND, blck, IGND, JBOD_SEEK_TO_BLOCK), NULL) == 0);

    // read
    assert(jbod_operation(op(IGND, IGND, IGND, JBOD_READ_BLOCK), buf) == 0); // read entire block into `buf`
    memcpy(read_buf, &buf[ofst], chunk);                                     // read chunk of `buf` into `read_buf`

    // post read
    read_buf   += chunk; // update pointer to read buffer
    bytes_read += chunk; // update number of bytes read
    start_addr += chunk; // update location in JBOD
  }

  // read operation successful
  assert(bytes_read == read_len);
  return bytes_read;
}