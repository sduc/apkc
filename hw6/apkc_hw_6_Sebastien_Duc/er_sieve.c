
/*
 * Sieving
 * Author: Sebastien Duc
 */

#include <stdio.h>
#include <stdlib.h> 
#include <stdint.h>
#include <assert.h>

#define F_PRIME_L 54
#define INIT_RANGE 256
#define FILENAME "gen_primes"

uint8_t first_primes [F_PRIME_L] = {
2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 
43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 
101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 
151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 
199, 211, 223, 227, 229, 233, 239, 241, 251
};


int main(int argc, const char **argv)
{
    uint64_t upper,lower,sqrt_upper;
    uint64_t s;

    if (argc < 2){
        fprintf(stderr,"Enter your sciper number\n");
        exit(EXIT_FAILURE);
    }
    s = (uint64_t) atoi(argv[1]);
    sqrt_upper = 16 * s;
    upper = sqrt_upper * sqrt_upper;
    lower = upper - sqrt_upper;
    


    uint8_t primes [sqrt_upper];
    uint8_t lower_primes [sqrt_upper - INIT_RANGE];
    
    // initialization of the two arrays
    uint8_t tmp_odd = 0;
    int i;
    for(i = 0; i < INIT_RANGE; ++i){
        primes[i] = tmp_odd;
        tmp_odd = !tmp_odd;
    }
    for(; i < sqrt_upper; ++i){
        primes[i] = tmp_odd;
        lower_primes[i - INIT_RANGE] = tmp_odd;
        tmp_odd = !tmp_odd;
    }

    // first use the precomputed primes
    for(i = 1; i < F_PRIME_L; ++i){
        uint64_t p = (uint64_t) first_primes[i];
        uint64_t tp = 2*p;
        uint64_t k = p;

        k = (INIT_RANGE/p + 1)*p;
        k += (k % 2 == 0) ? p : 0ull;

        while(k < sqrt_upper){
            lower_primes[k - INIT_RANGE] = 0;
            k += tp;
        }

        k = (lower/p + 1)*p;
        k += (k % 2 == 0) ? p : 0ull;

        while(k < upper){
            primes[k - lower] = 0;
            k += tp;
        }
    }
    
    // do the actual sieve
    for(uint64_t x = 257; x < sqrt_upper; x+=2){
        if (lower_primes[x - INIT_RANGE]){
            uint64_t tx = 2*x;
            uint64_t k = x; 
            
            k += tx;
            while(k < sqrt_upper){
                lower_primes[k - INIT_RANGE] = 0;
                k += tx;
            }

            k = (lower/x + 1)*x;
            k += (k % 2 == 0) ? x : 0ull;

            while(k < upper){
                primes[k - lower] = 0;
                k += tx;
            }
        }
    }


    // write the primes in file gen_primes
    FILE *fp = (FILE *) fopen (FILENAME,"w");
    for(uint64_t i = 0; i < sqrt_upper; ++i){
        if (primes[i]){
            fprintf(fp,"%llu\n",i + lower); 
        }
    }
    fclose(fp);
}


void sieve(uint64_t p, uint64_t k, uint8_t *primes, uint8_t *lower_primes, uint64_t sqrt_upper, uint64_t lower, uint64_t upper)
{
    uint64_t tp = 2*p;

    while(k < sqrt_upper){
        k += tp;
        lower_primes[k - INIT_RANGE] = 0;
    }

    k = (lower/p + 1)*p;
    while(k < upper){
        primes[k - lower] = 0;
        k += tp;
    }
}
