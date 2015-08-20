/**
 * Author: Sebastien Duc
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>


uint64_t str2uint64(const char *n , int base);
uint64_t inverse_mod2to64(uint64_t n);
int is_one(uint64_t n, int last_pos, int *new_pos);

int main(int argc,const char ** argv)
{
    uint64_t n;
    uint64_t inv;

    if (argc < 2){
        printf("Enter the number for which the inverse has to be computed\n");
        exit(EXIT_FAILURE);
    }
    
    n = str2uint64(argv[1],10);

    if (! (n & 1ull)){
        fprintf(stderr,"even number is not invertible\n");
        exit(EXIT_FAILURE);
    }
    
    inv = inverse_mod2to64(n);

    printf("%llu\n",inv);

}

uint64_t str2uint64(const char *n , int base)
{
    uint64_t res;
    errno = 0;
    
    res = strtoull(n,NULL,base);
    if (errno == EINVAL){
        fprintf(stderr,"error: this is not a valid number\n");
        exit(EXIT_FAILURE);
    }
    else if (errno == ERANGE){
        fprintf(stderr,"error: number is too large\n");
        exit(EXIT_FAILURE);
    }

    return res;
}

uint64_t inverse_mod2to64(uint64_t n)
{
    uint64_t inv = 1ull;
    uint64_t inv_times_n = n;
    int last_pos = 1;

    while (!is_one(inv_times_n,last_pos, &last_pos)) {
        inv += 1ull << last_pos;
        inv_times_n += n << last_pos;
    }


    return inv;
}

int is_one(uint64_t n, int last_pos, int *new_pos)
{
    uint64_t mask = 1ull << last_pos;

    while(!(mask & n) && last_pos < 64) {
        ++last_pos;
        mask <<= 1; 
    }

    if (last_pos > 63) return 1;
    *new_pos = last_pos;
    return 0;
}
