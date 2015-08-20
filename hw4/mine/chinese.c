#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h> //int64_t

void smoothing(int64_t b, int64_t* x, int64_t* d)
{
  while(*x > b / *d)
    *x -= b / *d;
}

void modInvBin(int64_t a, int64_t b, int64_t* x, int64_t* d)
{
  int64_t x0 = b;
  int64_t x1 = 1;
  int64_t d0 = b;
  int64_t d1 = a % b;

  int64_t xi, di, y, delta;

  while(d1 != 0)
  {
    //swap
    if(d0 < d1)
    {
      d0 = d0 ^ d1;
      d1 = d0 ^ d1;
      d0 = d0 ^ d1;

      x0 = x0 ^ x1;
      x1 = x0 ^ x1;
      x0 = x0 ^ x1;
    }

    //printf("%"PRId64",%"PRId64",%"PRId64",%"PRId64"\n",x0,x1,d0,d1);

    if(~(d0 - d1) & 0x01)
    {
      di = (d0 - d1) >> 1;
      delta = x0 - x1;
      if(~delta & 0x01)
       if(delta < 0)
          xi = delta + 2 * b >> 1;
        else
          xi = delta >> 1;
      else
        xi = (delta + b) >> 1;
    }
    else
    {
      while(~d0 & 0x1)
      {
        d0 >>= 1;
        if(~x0 & 0x1)
          x0 >>= 1;
        else
          x0 = (x0 + b) >> 1;
      }
      while(~d1 & 0x1)
      {
        d1 >>= 1;
        if(~x1 & 0x1)
          x1 >>= 1;
        else
          x1 = (x1 + b) >> 1;
      }
      continue;
    }

    x0 = x1;
    x1 = xi;
    d0 = d1;
    d1 = di;
  }

  *x = x0;
  *d = d0;

  smoothing(b,x,d);
}

int64_t chiremains(int64_t x, int64_t y, int64_t p, int64_t q)
{
  int64_t z, pinv, gcd;
 
  modInvBin(p, q, &pinv, &gcd);
  z = x + (y - x) * pinv * p;

  // re-bounding
  z %= p*q;
  if(z < 0)
    z += p*q;

  return z;
}

int main(int argc, char **argv)
{
  int64_t x, y, p, q;
  if(argc > 4)
  {
    sscanf(argv[1],"%"PRId64,&x);
    sscanf(argv[2],"%"PRId64,&y);
    sscanf(argv[3],"%"PRId64,&p);
    sscanf(argv[4],"%"PRId64,&q);
  }
  else
  {
    printf("Need at least four argument\n");
    return 1;
  }
  
  printf("Chinese remainder : %"PRId64"\n",chiremains(x,y,p,q));

  return 0;
}
