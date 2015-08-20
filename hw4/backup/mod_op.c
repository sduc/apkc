/*
 * Author: Sebastien Duc
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#include "mod_op.h"

int64_t mod_bound(int64_t x, int64_t mod);

void vanilla_mod_inverse(int64_t a, int64_t b, int64_t *d, int64_t *x)
{
    int64_t x_val = *x;
    int64_t x_next;
    int64_t d_val = *d;
    int64_t d_next;
    int64_t y;
    int64_t tmp;

    //initialization
    x_val = b;
    d_val = b;
    x_next = 1;
    d_next = a % b;
    while(d_next != 0){
        y = d_val/d_next;
        tmp = x_next;
        x_next = mod_bound(x_val - y*x_next, b);
        x_val = tmp;

        tmp = d_next;
        d_next = d_val % d_next;
        d_val = tmp;
    }

    *d = d_val;
    *x = x_val;
}


int64_t mod_bound(int64_t x, int64_t mod)
{
    while(x < 0){
        x += mod;
    }
    while(x > mod){
        x -= mod;
    }
    return x;
}
