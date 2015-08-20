/**
 * Authors: Bruno Studer, Sebastien Duc and Yann Schoenenberger
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BYTES 625
#define MAX_DIGITS 1500

void add(unsigned char *a, unsigned char *b, unsigned char *out);

unsigned char addbyte(unsigned char a, unsigned char b, unsigned char *carry);

void getnum(unsigned char *rop);

void output(char *op);

int strhextobytes(const char *strhex, size_t slen,  unsigned char *bytes);
int bytestohexstr(const unsigned char * bytes, size_t blen, char * strhex);

unsigned char b2h(char in);
char h2b(unsigned char in);

int main(int argc, char **argv)
{
    int n, i;
    unsigned char a[MAX_BYTES], b[MAX_BYTES];

    if (argc>1) n=atoi(argv[1]); else n=1;
    getnum(a);
    getnum(b);

    
    for (i=0; i<n; i++) {
        add(a,b,a);
    }
    output(a);
    return 0;
}

void add(unsigned char *a, unsigned char *b, unsigned char *out)
{
    int i;
    unsigned char carry = 0x00;
    for(i = 0; i < MAX_BYTES; ++i){
        out[i] = addbyte(a[i],b[i],&carry);
    }
}

unsigned char addbyte(const unsigned char a, const unsigned char b, unsigned char *carry)
{
    unsigned char out = a+b+*carry;
    *carry = (out < a || out < b);
    return out;
}

void getnum(unsigned char *rop)
{
    size_t ila=0, s, i;
    char *il=NULL;
    char tmp [2*MAX_BYTES];

    if (getline(&il,&ila,stdin)<=0) {
        fprintf(stderr,"reading number failed\n");
        exit(-1);
    }
    s=strlen(il)-1;
    if (s>2*MAX_BYTES) { fprintf(stderr,"number too big\n"); exit(-1); }
    for (i=0; i<s; i++) tmp[s-1-i]=il[i];
    for (; i<2*MAX_BYTES; i++) tmp[i]='0';
    if (ila) free(il);
    strhextobytes(tmp,2*MAX_BYTES,rop);
}

void output(char *op)
{
    int i, s;
    char str [2*MAX_BYTES];

    bytestohexstr(op,MAX_BYTES,str);

    for (s=2*MAX_BYTES-1; s; s--) if (str[s]!='0') break;
    for (i=0; i<=s; i++) putchar(str[s-i]);
    putchar('\n');
}


int strhextobytes(const char *strhex, size_t slen,  unsigned char *bytes)
{
    size_t i = 0;
    const char *pos = strhex;

    for(i = 0; i < slen; i+=2){
        bytes[i/2] = (b2h(strhex[i+1])<<4) ^ b2h(strhex[i]);
    }
    if (slen %2 != 0){++i; bytes[i] = strhex[i];}

    return 0;
}

int bytestohexstr(const unsigned char * bytes, size_t blen, char * strhex)
{
    size_t i,j=0;
    for(i=0; i < blen; ++i){
        strhex[j+1] = h2b(bytes[i] >> 4);
        strhex[j] = h2b(bytes[i] & 0x0f);
        j+=2;
    }
}

char h2b(unsigned char in)
{
    switch(in){
        case 0x0:
            return '0';
        case 0x1:
            return '1';
        case 0x2:
            return '2';
        case 0x3:
            return '3';
        case 0x4:
            return '4';
        case 0x5:
            return '5';
        case 0x6:
            return '6';
        case 0x7:
            return '7';
        case 0x8:
            return '8';
        case 0x9:
            return '9';
        case 0xA:
            return 'a';
        case 0xB:
            return 'b';
        case 0xC:
            return 'c';
        case 0xD:
            return 'd';
        case 0xE:
            return 'e';
        case 0xF:
            return 'f';
        default:
            fprintf(stderr,"Error: cannot convert hex digit\n");
            exit(1);
    }
}

unsigned char b2h(char in)
{
    switch(in){
        case '0':
            return 0x0;
        case '1':
            return 0x1;
        case '2':
            return 0x2;
        case '3':
            return 0x3;
        case '4':
            return 0x4;
        case '5':
            return 0x5;
        case '6':
            return 0x6;
        case '7':
            return 0x7;
        case '8':
            return 0x8;
        case '9':
            return 0x9;
        case 'a':
            return 0xA;
        case 'b':
            return 0xB;
        case 'c':
            return 0xC;
        case 'd':
            return 0xD;
        case 'e':
            return 0xE;
        case 'f':
            return 0xF;
        default:
            fprintf(stderr,"Error: cannot convert byte\n");
            exit(1);
    }
}
