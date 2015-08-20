/*
gcc -o checkadd checkadd.c -lgmp
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gmp.h"

void getnum(mpz_t rop)
{
  size_t ila=0, s, i;
  char *il = 0;

  mpz_init(rop);
  if (getline(&il,&ila,stdin)<=0) {
    fprintf(stderr,"reading number failed\n");
    exit(-1);
  }
  if (gmp_sscanf(il,"%Zd",rop)!=1) {
    fprintf(stderr,"number corrupt\n");
    exit(-1);
  }
}


int main(int argc, char **argv)
{
  int n;
  mpz_t a, b;

  if (argc>1) n=atoi(argv[1]); else n=1;
  getnum(a);
  getnum(b);
  mpz_addmul_ui(a,b,(unsigned long int)n);
  gmp_printf("%Zd\n",a);
  return 0;
}

