/*
 * Sieving
 * Author: Sebastien Duc
 */

#include <stdio.h>
#include <stdlib.h> 
#include <stdint.h>
#include <assert.h>

typedef uint8_t prime_t;

uint8_t is_prime(uint64_t prime, prime_t *primes, uint64_t lower);
void set_is_prime(uint64_t prime, uint8_t val, prime_t *primes, uint64_t lower);
void sieve(uint64_t n, prime_t *primes, uint64_t lower, uint64_t upper);

int main(int argc, const char **argv)
{
    uint64_t upper,lower,sqrt_upper;
    int s;
    uint64_t x, x_2, tx_2, y, y_2;
    uint64_t n,k;
    int prime_num;

    if (argc < 2){
        fprintf(stderr,"Enter your sciper number\n");
        exit(EXIT_FAILURE);
    }
    s = atoi(argv[1]);
    sqrt_upper = 16 * s;
    upper = sqrt_upper * sqrt_upper;
    lower = upper - sqrt_upper;

    assert(sqrt_upper < lower);
    
    prime_t *primes = (prime_t *) calloc (sqrt_upper, sizeof(prime_t));
    if (!primes) {
        fprintf(stderr,"Error: could not alloc memory\n");
        exit(EXIT_FAILURE);
    }

    for(x = 1; x <= sqrt_upper; ++x){
        for(y = 1; y <= sqrt_upper; ++y){
            x_2 = x*x;
            y_2 = y*y;
            tx_2 = 3*x_2;
        
            n = tx_2 + y_2;

            if(n <= upper && n % 12 == 7){
                if (n <= sqrt_upper){
                    sieve(n,primes,lower,upper);
                }
                else if (n >= lower){
                    set_is_prime(n,1,primes,lower);
                }
            }

            n += x_2;

            if(n <= upper && (n % 12 == 1 || n % 12 == 5)){
                if (n <= sqrt_upper){
                    sieve(n,primes,lower,upper);
                }
                else if (n >= lower){
                    set_is_prime(n,1,primes,lower);
                }
            }

            n = tx_2 - y_2;

            if(x > y && n <= upper && n % 12 == 11){
                if (n <= sqrt_upper){
                    sieve(n,primes,lower,upper);
                }
                else if (n >= lower){
                    set_is_prime(n,1,primes,lower);
                }
            }

        }
    }

}

void init_prime_t(prime_t *primes, size_t len)
{
    int i;
    for(i = 0; i < len; ++i){
        primes[i] = 0;
    }
}

void sieve(uint64_t n, prime_t *primes, uint64_t lower, uint64_t upper)
{
    while(n < lower)  n *= n;
    while(n < upper){
        set_is_prime(n,0,primes,lower);
        n *= n;
    }
}

uint8_t is_prime(uint64_t prime, prime_t *primes, uint64_t lower)
{
    return primes[prime - lower];
}

void set_is_prime(uint64_t prime, uint8_t val, prime_t *primes, uint64_t lower)
{
   primes[prime - lower] = val; 
}



