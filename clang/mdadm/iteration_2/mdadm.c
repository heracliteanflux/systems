/*    mdadm.c    Multiple Disk and Device Administration
 *
 *    Iteration 2
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
      int is_writabl    = 0;                        // not writable = 0, writable = 1


// auxiliary function - construct a 32-bit operation
uint32_t op (uint32_t rsvd, uint32_t blck, uint32_t disk, uint32_t cmnd) {
  return              rsvd << 18   | blck << 10   | disk <<  6   | cmnd;
  //        xxxx xxxx xxxx xxxx xx | xx xxxx xx   | xx xx        | xx xxxx
}


// auxiliary function - recompute location in JBOD in terms of disk, block, and specific address
void addr (uint32_t *start_addr, uint32_t *disk, uint32_t *blck, uint32_t *ofst) {
  *disk = *start_addr / DISK_SIZE;               // 0..(2^20 - 1) / 2^16 = 0..(2^4 - 1) --> a number between 0 and  16
  *blck = *start_addr % DISK_SIZE / BLCK_SIZE;   // 0..(2^16 - 1) /  2^8 = 0..(2^8 - 1) --> a number between 0 and 255
  *ofst = *start_addr % DISK_SIZE % BLCK_SIZE;   // 0..( 2^8 - 1)                       --> a number between 0 and 255
}


/*    mount the linear device
 *
 *    return
 *        1 on succuss
 *       -1 on failure
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


/*    unmount the linear device
 *
 *    return
 *        1 on succuss
 *       -1 on failure
 */
int mdadm_unmount (void) {
  if                     (is_mounted == 0) return -1;   // failure!   --> if JBOD is already unmounted then fail this attempt to unmount
  uint32_t opcode = op(IGND, IGND, IGND, JBOD_UNMOUNT); // otherwise, proceed with unmount
  int jbod_result = jbod_operation(opcode, NULL);
  if (jbod_result == 0) { is_mounted  = 0; return  1; } // success!   --> JBOD successfully unmounted
  else                                     return -1;   // failure!   --> JBOD could not unmount for some reason
}


/*    enable write
 *
 *    return
 *        1 on succuss
 *       -1 on failure
 */
int mdadm_write_permission (void){
  if                     (is_writabl == 1) return -1;            // failure!   --> if JBOD is already writable then fail this attempt to enable write
  uint32_t opcode = op(IGND, IGND, IGND, JBOD_WRITE_PERMISSION); // otherwise, proceed with write enable
  int jbod_result = jbod_operation(opcode, NULL);
  if (jbod_result == 0) { is_writabl  = 1; return  1; }          // success!   --> JBOD successfully enabled write permission
  else                                     return -1;            // failure!   --> JBOD could not enable write permission for some reason
}


/*    disable write
 *
 *    return
 *        1 on succuss
 *       -1 on failure
 */
int mdadm_revoke_write_permission (void){
  if                     (is_writabl == 0) return -1;                   // failure!   --> if JBOD is already non writable then fail this attempt to disable write
  uint32_t opcode = op(IGND, IGND, IGND, JBOD_REVOKE_WRITE_PERMISSION); // otherwise, proceed with write disable
  int jbod_result = jbod_operation(opcode, NULL);
  if (jbod_result == 0) { is_writabl  = 0; return  1; }                 // success!   --> JBOD successfully disabled write permission
  else                                     return -1;                   // failure!   --> JBOD could not disable write permission for some reason
}


/*    read `read_len` bytes into `read_buf` starting at address `start_addr`
 *
 *    return
 *        num bytes read on succuss
 *       -1              on failure
 */
int mdadm_read(uint32_t start_addr, uint32_t read_len, uint8_t *read_buf)  {
  uint32_t disk;
  uint32_t blck;
  uint32_t ofst;

  // input validation
  if (!is_mounted)                                  return -1;   // JBOD must be mounted
  if (!(0 <= start_addr && start_addr < JBOD_SIZE)) return -1;   // 0 <= start_addr < 1,048,576 (2^20)
  if (!(0 <= read_len   && read_len  <= MAX_RDLEN)) return -1;   // 0 <= read_len   <     1,024 (2^10)
  if (!(     start_addr  + read_len  <= JBOD_SIZE)) return -1;   // start_addr + read_len <= 1,048,576
  if (read_buf == NULL && read_len > 0)             return -1;

  // initialization - seek to correct disk and block of `start_addr`
  addr(&start_addr, &disk, &blck, &ofst);
  assert(jbod_operation(op(IGND, IGND, disk, JBOD_SEEK_TO_DISK),  NULL) == 0);
  assert(jbod_operation(op(IGND, blck, IGND, JBOD_SEEK_TO_BLOCK), NULL) == 0);

  // read
  int bytes_to_be_read = read_len;
  int bytes_read       = 0;
  while (bytes_to_be_read > 0) {                                                              // `read_len` must be at least 1
    int chunk = bytes_to_be_read >= (BLCK_SIZE - ofst) ? BLCK_SIZE - ofst : bytes_to_be_read; // how many B to read? 256 - (0..255) = 1..256

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

    //if      (disk >= 16) { assert(jbod_operation(op(IGND, IGND,    0, JBOD_SEEK_TO_DISK), NULL) == 0); }
    if (blck ==  0) { assert(jbod_operation(op(IGND, IGND, disk, JBOD_SEEK_TO_DISK), NULL) == 0); } // if the updated blck value is 0 then seek to the next disk
  }

  // successful read
  assert(bytes_read == read_len);
  return bytes_read;
}


/*    write `write_len` bytes from `write_buf` into JBOD starting at address `start_addr`
 *
 *    return
 *        num bytes written on succuss
 *       -1                 on failure
 */
int mdadm_write (uint32_t start_addr, uint32_t write_len, const uint8_t *write_buf) {
  uint32_t disk;
  uint32_t blck;
  uint32_t ofst;

  // input validation
  if (!is_mounted)                                  return -1;   // JBOD must be mounted
  if (!is_writabl)                                  return -1;   // JBOD must be write enabled
  if (!(0 <= start_addr && start_addr < JBOD_SIZE)) return -1;   // 0 <= start_addr < 1,048,576 (2^20)
  if (!(0 <= write_len  && write_len <= MAX_RDLEN)) return -1;   // 0 <= write_len  <     1,024 (2^10)
  if (!(     start_addr  + write_len <= JBOD_SIZE)) return -1;   // start_addr + write_len <= 1,048,576
  if (write_buf == NULL && write_len  > 0)          return -1;

  // initialization - seek to correct disk and block of `start_addr`
  addr(&start_addr, &disk, &blck, &ofst);
  assert(jbod_operation(op(IGND, IGND, disk, JBOD_SEEK_TO_DISK),  NULL) == 0);
  assert(jbod_operation(op(IGND, blck, IGND, JBOD_SEEK_TO_BLOCK), NULL) == 0);

  // write
  int bytes_to_be_written = write_len;
  int bytes_written       = 0;
  while (bytes_to_be_written > 0) {                                                                 // `read_len` must be at least 1
    int chunk = bytes_to_be_written >= (BLCK_SIZE - ofst) ? BLCK_SIZE - ofst : bytes_to_be_written; // how many B to read? 256 - (0..255) = 1..256

    // write operation
    uint8_t buf[BLCK_SIZE];                                                   // 256-B buffer
    memcpy(&buf[ofst], write_buf, chunk);                                     // write chunk of `write_buf` into `buf`
    assert(jbod_operation(op(IGND, IGND, IGND, JBOD_WRITE_BLOCK), buf) == 0); // write entire `buf` into block

    // post write operation
    write_buf           += chunk;              // update pointer `read_buf`
    bytes_to_be_written -= chunk;              // update        the number of bytes to be read
    bytes_written       += chunk;              // keep track of the number of bytes       read
    start_addr          += chunk;              // recompute location in JBOD
    addr(&start_addr, &disk, &blck, &ofst); // recompute location in JBOD

    //if      (disk >= 16) { assert(jbod_operation(op(IGND, IGND,    0, JBOD_SEEK_TO_DISK), NULL) == 0); }
    if (blck ==  0) { assert(jbod_operation(op(IGND, IGND, disk, JBOD_SEEK_TO_DISK), NULL) == 0); } // if the updated blck value is 0 then seek to the next disk
  }

  // successful write
  assert(bytes_written == write_len);
  return bytes_written;
}