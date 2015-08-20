/*
gcc -o chgbase chgbase.c -lgmp
*/
#include <stdio.h>
#include "gmp.h"

int main(int argc, char **argv)
{
  int ibase, obase;
  mpz_t aux;

  if (argc!=3) { fprintf(stderr,"Usage: chgbase ibase obase\n"); return -1; }
  ibase=atoi(argv[1]); obase=atoi(argv[2]);  
  if ((ibase<2) || (ibase>62) || (obase<2) || (obase>62)) {
    fprintf(stderr,"ibase and obase must be integers in [2,62]\n"); 
    return -1;
  }
  mpz_init(aux);
  if (!mpz_inp_str(aux,stdin,ibase)) {
    fprintf(stderr,"error in input\n");
    return -1;
  }
  if (!mpz_out_str(stdout,obase,aux)) {
    fprintf(stderr,"error in output\n");
    return -1;
  }
  printf("\n");
  return 0;
}
