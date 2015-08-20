#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#include "mod_op.h"

/*
 * find the smallest k>0 s.t. z_k = x (mod p) and z_k = y (mod q) where z_k = x + k*p
 * (i.e. we apply exercise 4.2.1)
 */
uint64_t find_k(uint64_t p, uint64_t q, uint64_t x, uint64_t y);

int main(int argc, const char **argv)
{
    uint64_t p,q,x,y,z;
    
    if(argc > 4)
    {
        sscanf(argv[1], "%"PRId64, &p);
        sscanf(argv[2], "%"PRId64, &q);
        sscanf(argv[3], "%"PRId64, &x);
        sscanf(argv[4], "%"PRId64, &y);
    }
    else
    {
        printf("Need to enter four arguments:\n");
        printf("$> ./chinese_reminder p q x y\n");
        return 1;
    }

    z = x + find_k(p,q,x,y) * p;
    printf("%llu\n", z);
}

uint64_t find_k(uint64_t p, uint64_t q, uint64_t x, uint64_t y)
{
    int64_t k = y - x;
    uint64_t inv_p_mod_q;
    uint64_t gcd;

    mod_inv(p, q, &gcd, &inv_p_mod_q);

    if (gcd != 1) {
        fprintf(stderr,"Error: p and q are not coprime.\n");
        exit(EXIT_FAILURE);
    }
    
    k *= inv_p_mod_q;
    
    while (k < 0) k += ((int64_t)q);
    return (uint64_t)k;
}
