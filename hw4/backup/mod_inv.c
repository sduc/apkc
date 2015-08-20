/*
 * Author: Sebastien Duc
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#include "mod_op.h"

int main(int argc, const char **argv)
{
    int64_t a;
    int64_t b;
    int64_t d,x;

    if(argc > 2)
    {
        sscanf(argv[1],"%"PRId64,&a);
        sscanf(argv[2],"%"PRId64,&b);
    }
    else
    {
        printf("Need at least two argument\n");
        return 1;
    }

    if(~b & 0x1)
    {
        printf("b must be an odd integer\n");
        return 1;
    }

    mod_inv(a,b,&d,&x);

    printf("The inverse is : %lld\n",x);
    printf("The gcd is : %lld\n",d);

}
