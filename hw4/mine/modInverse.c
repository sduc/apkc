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

    printf("%"PRId64",%"PRId64",%"PRId64",%"PRId64"\n",x0,x1,d0,d1);

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
}

void modInvSym(int64_t a, int64_t b, int64_t* x, int64_t* d)
{
  int64_t x0 = b;
  int64_t x1 = 1;
  int64_t d0 = b;
  int64_t d1 = a % b;

  int64_t xi, di, y;

  while(d1 != 0)
  {
    printf("%"PRId64",%"PRId64",%"PRId64",%"PRId64"\n",x0,x1,d0,d1);

    y = d0 / d1;
    if(d0 % d1 > d1/2 && d1 > 0)
      y++;

    xi = x0 - y * x1;
    while(xi < 0)
      xi += b;
    while(xi > b)
      xi -= b;
    di = d0 - y * d1;

    x0 = x1;
    x1 = xi;
    d0 = d1;
    d1 = di;
  }

  // special case
  if(d0 < 0)
  {
    x0 = b - x0;
    d0 *= -1;
  }

  *x = x0;
  *d = d0;
}

void modInv(int64_t a, int64_t b, int64_t* x, int64_t* d)
{
  int64_t x0 = b;
  int64_t x1 = 1;
  int64_t d0 = b;
  int64_t d1 = a % b;

  int64_t xi, di, y;

  while(d1 != 0)
  {
    printf("%"PRId64",%"PRId64",%"PRId64",%"PRId64"\n",x0,x1,d0,d1);

    y = d0 / d1;

    xi = x0 - y * x1;
    while(xi < 0)
      xi += b;
    di = d0 - y * d1;

    x0 = x1;
    x1 = xi;
    d0 = d1;
    d1 = di;
  }

  *x = x0;
  *d = d0;
}

int main(int argc, char **argv)
{
  int64_t a, b, d, x;
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
  printf("\nStandard : \n\n");
  modInv(a,b,&x,&d);

  printf("d = %"PRId64"\n",d);
  printf("x = %"PRId64"\n",x);
  smoothing(b,&x,&d);
  printf("x' = %"PRId64"\n",x);

  printf("\nSymetric : \n\n");
  modInvSym(a,b,&x,&d);

  printf("d = %"PRId64"\n",d);
  printf("x = %"PRId64"\n",x);
  smoothing(b,&x,&d);
  printf("x' = %"PRId64"\n",x);

  printf("\nBinary : \n\n");
  modInvBin(a,b,&x,&d);

  printf("d = %"PRId64"\n",d);
  printf("x = %"PRId64"\n",x);
  smoothing(b,&x,&d);
  printf("x' = %"PRId64"\n",x);
  return 0;
}
