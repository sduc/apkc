#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#include "mod_op.h"

#define SWAP(x,y) x = x ^ y; y = x ^ y; x = x ^ y; 

int64_t mod_bound(int64_t x, int64_t mod);

void vanilla_mod_inverse(int64_t a, int64_t b, int64_t *d, int64_t *x)
{
    int64_t x_val = *x;
    int64_t x_next;
    int64_t d_val = *d;
    int64_t d_next;
    int64_t y;
    int64_t tmp;

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

void sym_mod_inverse(int64_t a, int64_t b, int64_t *d, int64_t *x)
{
    int64_t x0 = b;
    int64_t x1 = 1;
    int64_t d0 = b;
    int64_t d1 = a % b;
    
    int64_t xi, di, y;
    
    while(d1 != 0) {
        y = d0 / d1;
        if(d0 % d1 > d1/2 && d1 > 0) y++;
    
        xi = x0 - y * x1;
        while(xi < 0) xi += b;
        while(xi > b) xi -= b;
        di = d0 - y * d1;
        
        x0 = x1;
        x1 = xi;
        d0 = d1;
        d1 = di;
    }
    
    if(d0 < 0) {
        x0 = b - x0;
        d0 *= -1;
    }
    
    *x = x0;
    *d = d0;
}

void bin_mod_inverse(int64_t a, int64_t b, int64_t *d, int64_t *x)
{
    int64_t x0 = b;
    int64_t x1 = 1;
    int64_t d0 = b;
    int64_t d1 = a % b;
    
    int64_t xi, di, y, delta, r;
    
    while(d1 != 0) {
        if(d0 < d1) {
            SWAP(d0, d1);
            SWAP(x0, x1);
        }
        
        if(~(d0 - d1) & 0x01) {
            di = (d0 - d1) >> 1ull;
            delta = x0 - x1;
            if(~delta & 0x01) xi = delta >> 1ull;
            else xi = (delta + b) >> 1ull;
        }
        else {
            while(~d0 & 0x1) {
                d0 >>= 1ull;
                if(~x0 & 0x1) x0 >>= 1ull;
                else x0 = (x0 + b) >> 1ull;
            }
            while(~d1 & 0x1) {
                d1 >>= 1ull;
                if(~x1 & 0x1) x1 >>= 1ull;
                else x1 = (x1 + b) >> 1ull;
            }
            continue;
        }
        
        x0 = x1;
        x1 = xi;
        d0 = d1;
        d1 = di;
    }

    *x = mod_bound(x0, b);
    *d = d0;
}

int64_t mod_bound(int64_t x, int64_t mod)
{
    while(x < 0) x += mod;
    while(x > mod) x -= mod;
    return x;
}
