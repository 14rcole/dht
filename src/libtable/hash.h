#include <stdint.h>

#ifndef HASH_H
#define HASH_H

#ifndef FNV_CONSTANTS
#define FNV_CONSTANTS
/* to compute prime and offset:
 * n = 2^s; n is the number of bits (32-bit here)
 *   so s = log2(n) (here s = 5)
 * (this function does not work with s < 5 or s > 10)
 * t = floor((5 + 2^s)/12)
 *   so t = floor(37/12) = 3
 * The fnv prime is the smallest prime number p of the form
 *    p = 256^t + 2^8 + b; where b is a constant with the following constraints:
 *    0 < b < 2^8
 *    the number of 1 bits in b is either 4 or 5
 *    p mod (2^40-2^24-1) > (2^24+2^8+2^7)
 * Disclaimer: I didn't actually go through the legwork to verify b (these
 * values are easy to find online), but I did verify the rest of the formulas
 * 
*/
#define FNV_PRIME_32 16777619
#define FNV_OFFSET_32 2166136261U
#define FNV_MASK_24 (((uint32_t)1<<24)-1)
#endif

uint32_t FNV32(const char *s);
uint32_t FNV24(const char *s);

#endif
