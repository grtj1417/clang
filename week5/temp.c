#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define	MAXDIGITS	100		/* maximum length bignum */ 

#define PLUS		1		/* positive sign bit */
#define MINUS		-1		/* negative sign bit */

typedef struct {
    char digits[MAXDIGITS];         /* represent the number */
    int signbit;			/* 1 if positive, -1 if negative */ 
    int lastdigit;			/* index of high-order digit */
} bignum;

void print_bignum(bignum *n)
{
    int i;

    if (n->signbit == MINUS) printf("- ");
    for (i = n->lastdigit; i >= 0; i--)
        printf("%c", '0' + n->digits[i]);

    printf("\n");
}

void int_to_bignum(int s, bignum *n)
{
    int i;				/* counter */
    int t;				/* int to work with */

    if (s >= 0) n->signbit = PLUS;
    else n->signbit = MINUS;

    for (i = 0; i < MAXDIGITS; i++) n->digits[i] = (char) 0;

    n->lastdigit = -1;

    t = abs(s);

    while (t > 0) {
        n->lastdigit++;
        n->digits[n->lastdigit] = (t % 10);
        t = t / 10;
    }

    if (s == 0) n->lastdigit = 0;
}

void initialize_bignum(bignum *n)
{
    int_to_bignum(0, n);
}

int max(int a, int b)
{
    if (a > b) return (a);
    else return (b);
}

/*	c = a +-/* b;	*/

void add_bignum(bignum *a, bignum *b, bignum *c);

void subtract_bignum(bignum *a, bignum *b, bignum *c);

void zero_justify(bignum *n);

int compare_bignum(bignum *a, bignum *b)
{
    int i;				//counter 

    if ((a->signbit == MINUS) && (b->signbit == PLUS)) return (PLUS);
    if ((a->signbit == PLUS) && (b->signbit == MINUS)) return (MINUS);

    if (b->lastdigit > a->lastdigit) return (PLUS * a->signbit);
    if (a->lastdigit > b->lastdigit) return (MINUS * a->signbit);

    for (i = a->lastdigit; i >= 0; i--) {
        if (a->digits[i] > b->digits[i]) return (MINUS * a->signbit);
        if (b->digits[i] > a->digits[i]) return (PLUS * a->signbit);
    }

    return (0);
}
void multiply_bignum(bignum *a, bignum *b, bignum c)
{
    bignum row; // represent shifted row 
    bignum tmp; // placeholder bignum 
    int i,j; // counters 
    initialize_bignum(c);

    row = *a;

    for (i=0; i<=b->lastdigit; i++) {
        for (j=1; j<=b->digits[i]; j++) {
            add_bignum(c,&row,&tmp);
            *c = tmp;
        }
        digit_shift(&row,1);
    }

    c->signbit = a->signbit * b->signbit;

    zero_justify(c);
}

void divide_bignum(bignum *a, bignum *b, bignum c)
{
    bignum row; // represent shifted row 
    bignum tmp; // placeholder bignum 
    int asign, bsign; // temporary signs 
    int i,j; // counters 
    initialize_bignum(&c);
    c->signbit = a->signbit * b->signbit;

    asign = a->signbit;
    bsign = b->signbit;

    a->signbit = PLUS;
    b->signbit = PLUS;

    initialize_bignum(&row);
    initialize_bignum(&tmp);

    c->lastdigit = a->lastdigit;

    for (i=a->lastdigit; i>=0; i--) {
        digit_shift(&row,1);
        row.digits[0] = a->digits[i];
        c->digits[i] = 0;
        while (compare_bignum(&row,b) != PLUS) {
            c->digits[i] ++;
            subtract_bignum(&row,b,&tmp);
            row = tmp;
        }
    }

    zero_justify(c);

    a->signbit = asign;
    b->signbit = bsign;
}

int main()
{
    bignum a,b,c;
    int_to_bignum(123,&a);
    int_to_bignum(456,&b);

    multiply_bignum(&a,&b,&c);

    print_bignum(&c);

    return 0;
}