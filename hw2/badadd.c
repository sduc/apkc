/*
gcc -O2 -o badadd badadd.c
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void getnum(char *rop)
{
  size_t ila=0, s, i;
  char *il=NULL;

  if (getline(&il,&ila,stdin)<=0) {
    fprintf(stderr,"reading number failed\n");
    exit(-1);
  }
  s=strlen(il)-1;
  if (s>1500) { fprintf(stderr,"number too big\n"); exit(-1); }
  for (i=0; i<s; i++) rop[s-1-i]=il[i];
  for (; i<1500; i++) rop[i]='0';
  if (ila) free(il);
}


void add(char *rop, char *op1, char *op2)
{
  int i, x, x1, x2, c;

  for (i=0,c=0; i<1500; i++) {
    x1=(int)(op1[i]-'0');
    x2=(int)(op2[i]-'0');
    x=x1+x2+c;
    c=x/10;
    x=x%10;
    rop[i]='0'+(char)x;
  }
}


void output(char *op)
{
  int i, s;

  for (s=1500-1; s; s--) if (op[s]!='0') break;
  for (i=0; i<=s; i++) putchar(op[s-i]);
  putchar('\n');
}


int main(int argc, char **argv)
{
  int ibase, obase, n, i;
  char a[1500], b[1500];

  if (argc>1) n=atoi(argv[1]); else n=1;
  getnum(a);
  getnum(b);
  for (i=0; i<n; i++) add(a,a,b);
  output(a);
  return 0;
}

