#ifndef __MOD_OP_H_INCLUDED__
#define __MOD_OP_H_INCLUDED__

#include <inttypes.h>

#define mod_inv sym_mod_inverse

/**
 * Compute inverse of a mod b in x and return the gcd in d.
 */
void vanilla_mod_inverse(int64_t a, int64_t b, int64_t *d, int64_t *x);

void sym_mod_inverse(int64_t a, int64_t b, int64_t *d, int64_t *x);

void bin_mod_inverse(int64_t a, int64_t b, int64_t *d, int64_t *x);

#endif/*__MOD_OP_H_INCLUDED*/
