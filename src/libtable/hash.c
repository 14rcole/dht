#include <string.h>
#include <stdint.h>

#include "hash.h"

/* Implementation of the FNV hashing algorithm
 * FNV prime is a prime number with good dispersion properties
 * This means that the hash will be evenly and randomly distributed
 * To read more about the formula for fnv primes, check the wiki page
*/
uint32_t FNV32(const char *s) {
  uint32_t hash = FNV_OFFSET_32, i;
  for (i = 0; i < strlen(s); i++) {
    hash = hash  ^ (s[i]); // xor next byte into the hash
    hash = hash * FNV_PRIME_32; // Multiply by the fnv prime
  }
  return hash;
}

/* We will use a 24-bit hash because it gives us 17 megabytes of address space.
 * After distributing the system, when more memory is available, the set of
 * valid addresses can be increased here in order to better prevent 
 *
 * To make an n-bit hash into an m-bit hash (where n is the power of 2 greater
 * than n), we use a process called xor-folding.  Here, n is 32 and m is 24.  We
 * create a mask, which, starting from the right, is m 1's with the remaining
 * spots being 0's, and AND it with the hash so that the leftmost (n-m) bits are
 * 0. We then XOR this with the n-bit hash shifted to the right by m.  At this
 * point in time, for a 24-bit hash, the number stored in memory will consist
 * of (from left to right): 8 0's, the left-most 16 bits of the original hash,
 * and the rightmost 8 bits of the original hash ANDed with the 8 bits to the
 * left of it in the original hash
*/
uint32_t FNV24(const char *s) {
  uint32_t hash32, hash24;
 
  hash32 = FNV32(s);
  hash24 = (hash32>>24) ^ (hash32 & FNV_MASK_24);
}

