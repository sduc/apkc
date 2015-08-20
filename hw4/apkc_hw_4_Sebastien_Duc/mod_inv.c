#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#include "mod_op.h"

int main(int argc, const char **argv)
{
    int64_t a;
    int64_t b;
    int64_t d, x;

    if(argc > 2)
    {
        sscanf(argv[1], "%"PRId64, &a);
        sscanf(argv[2], "%"PRId64, &b);
    }
    else
    {
        printf("Need at least two arguments\n");
	printf("$> ./mod_inv a b\n");
        return 1;
    }

    if(~b & 0x1)
    {
        printf("b must be an odd integer.\n");
        return 1;
    }

    printf("Vanilla modular inversion:\n");
    
    vanilla_mod_inverse(a,b,&d,&x);

    printf("The gcd of %lld and %lld is %lld\n", a, b, d);
    if(d == 1) printf("The inverse modulo %lld of %lld is %lld\n", b, a, x);
    else  printf("x is %lld\n", x);

    printf("Symmetric modular inversion:\n");
    
    sym_mod_inverse(a,b,&d,&x);

    printf("The gcd of %lld and %lld is %lld\n", a, b, d);
    if(d == 1) printf("The inverse modulo %lld of %lld is %lld\n", b, a, x);
    else  printf("x is %lld\n", x);

    printf("Binary modular inversion:\n");
    
    bin_mod_inverse(a,b,&d,&x);

    printf("The gcd of %lld and %lld is %lld\n", a, b, d);
    if(d == 1) printf("The inverse modulo %lld of %lld is %lld\n", b, a, x);
    else  printf("x is %lld\n", x);

    return 0;
}
