/*    cache.c
 */


#include <assert.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cache.h"
#include "jbod.h"

extern const int BLCK_SIZE; // 256 B per blck

static cache_entry_t *cache       = NULL;
static int            cache_size  = 0;
static int            num_queries = 0;
static int            num_hits    = 0;
       int            is_cached   = 0;


/********************************************************************************
 *
 *                    Cache Auxiliary
 *
 ********************************************************************************/


int cache_hit (int disk_num, int block_num, int i) {
  return (cache[i].valid == true
            && disk_num  == cache[i].disk_num
            && block_num == cache[i].block_num);
}


/********************************************************************************
 *
 *                    Cache
 *
 ********************************************************************************/


/* cache_create
 * 
 *   dynamically allocate space for `num_entries` cache entries of type `cache_entry_t`:
 *
 *   typedef struct {
 *     bool    valid;                  // indicates whether the cache entry is valid
 *     int     disk_num;               // disk ID
 *     int     block_num;              // blck ID
 *     uint8_t block[JBOD_BLOCK_SIZE]; // blck data
 *     int     num_accesses;           // the total number of times this cache block was accessed (read and write)
 *   } cache_entry_t;
 *
 *   return
 *     -1 on failure
 *      1 on success
 */
int cache_create (int num_entries) {
  if (is_cached == 1)                                                                 return -1; // calling this function twice without an intervening call to function `cache_destroy` fails
  if (!(pow(2, 1) <= num_entries && num_entries <= pow(2, 12)))                       return -1; // 2^1 <= num_entries <= 2^12
  if ((cache = (cache_entry_t *)malloc(num_entries * sizeof(cache_entry_t))) == NULL) return -1;
  cache_size = num_entries;
  is_cached  = 1;

  for (int i = 0; i < num_entries; i++)
    cache[i].valid = false;

  return 1;
}


/* return
 *   -1 on failure
 *    1 on success
 */
int cache_destroy (void) {
  if (is_cached == 0) return -1;    // if function `cache_destroy` 

  free(cache);
  cache      = NULL;
  cache_size = 0;
  is_cached  = 0;

  return 1;
}


/* return
 *   -1 on failure
 *    1 on success
 */
int cache_lookup (int disk_num, int block_num, uint8_t *buf) {
  /*-------------------- input validation */
  if (buf == NULL)      return -1;        // the buffer must not be NULL
  /*--------------------------------------*/

  num_queries += 1;                           // increment the lookup counter each time this function is called

  for (int i = 0; i < cache_size; i++) {      // linear-time scan of  the cache
    if (cache_hit(disk_num, block_num, i)) {  //   if the block is in the cache: cache hit!
      memcpy(buf, cache[i].block, BLCK_SIZE); //     1. copy the cache block into the buffer
      num_hits              += 1;             //     2. increment the cache hit counter
      cache[i].num_accesses += 1;             //     3. increment the cache block's access counter

      return 1;
    }
  }

  return -1;
}


/* return
 *   true  if the cache is     enabled
 *   false if the cache is not enabled
 */
int cache_insert (int disk_num, int block_num, const uint8_t *buf) {
  // input validation
  if (buf == NULL)                                     return -1;    // the buffer must not be NULL
  if (!(0 <= disk_num  && disk_num  <= pow(2, 4) - 1)) return -1;    // 0 <= disk_num <=  15
  if (!(0 <= block_num && block_num <= pow(2, 8) - 1)) return -1;    // 0 <= blck_num <= 255

  // check that the entry does not already exist in the cache
  for (int i = 0; i < cache_size; i++) {
    if (cache_hit(disk_num, block_num, i))
      return -1;
  }

  int min_accesses = 0;                        // the index of the LFU cache entry
  for (int i = 0; i < cache_size; i++) {       // linear-time scan of  the cache
    if (cache[i].valid == false) {             //   find and fill the first unused cache entry and return
      cache[i].valid        = true;
      cache[i].disk_num     = disk_num;
      cache[i].block_num    = block_num;
      memcpy(cache[i].block, buf, BLCK_SIZE);
      cache[i].num_accesses = 1;

      return 1;
    }
    else if (cache[min_accesses].num_accesses  //   or else if the cache is full then run LFU replacement policy
           > cache[i]           .num_accesses)
      min_accesses = i;
  }

  // this code block only runs when the cache is full and the LFU replacement policy is run
  cache[min_accesses].disk_num     = disk_num;
  cache[min_accesses].block_num    = block_num;
  memcpy(cache[min_accesses].block, buf, BLCK_SIZE);
  cache[min_accesses].num_accesses = 1;

  return 1;
}


void cache_update (int disk_num, int block_num, const uint8_t *buf) {
  for (int i = 0; i < cache_size; i++) {         // linear-time scan of  the cache
    if (cache_hit(disk_num, block_num, i)) {     //   if the block is in the cache: cache hit!
      memcpy(cache[i].block, buf, BLCK_SIZE);    //     1. copy the buffer data into the cache block
      cache[i].num_accesses += 1;                //     2. increment the cache block's access counter
    }
  }
}


/* return
 *   true  if the cache is     enabled
 *   false if the cache is not enabled
 */
bool cache_enabled (void) {
  return cache != NULL && cache_size > 0;
}


void cache_print_hit_rate (void) {
	fprintf(stderr, "num_hits: %d, num_queries: %d\n",   num_hits,  num_queries);
	fprintf(stderr, "Hit rate: %5.1f%%\n", 100 * (float) num_hits / num_queries);
}