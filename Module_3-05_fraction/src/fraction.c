#include <stdlib.h>
#include <stdio.h>
#include "fraction.h"

/* Algorithm for determining greatest common divisor, needed in (d) */
/* The function returns gcd between the two parameters, u and v */
/* Taken from http://en.wikipedia.org/wiki/Binary_GCD_algorithm */
unsigned int gcd(unsigned int u, unsigned int v)
{
    // simple cases (termination)
    if (u == v)
        return u;
 
    if (u == 0)
        return v;
 
    if (v == 0)
        return u;
 
    // look for factors of 2
    if (~u & 1) // u is even
    {
        if (v & 1) // v is odd
            return gcd(u >> 1, v);
        else // both u and v are even
            return gcd(u >> 1, v >> 1) << 1;
    }
 
    if (~v & 1) // u is odd, v is even
        return gcd(u, v >> 1);
 
    // reduce larger argument
    if (u > v)
        return gcd((u - v) >> 1, v);
 
    return gcd((v - u) >> 1, u);
}

struct fraction_st {
    unsigned int num;
    unsigned int denom;
};

/* Exercise a: Set fraction
 * Parameters: numerator and denominator
 * Returns: pointer to allocated fraction
 */
Fraction* setFraction(unsigned int numerator, unsigned int denominator)
{
    Fraction* frac = malloc(sizeof(struct fraction_st));
    frac->num = numerator;
    frac->denom = denominator;
    return frac;
}

unsigned int getNum(const Fraction *f)
{
    return f->num;
}

unsigned int getDenom(const Fraction *f)
{
    return f->denom;
    
}

void freeFraction(Fraction *f)
{
    free(f);
}


/* Exercise b: Compare values
 * Parameters: two fractions to be compared
 * Returns:
 * -1 if a is smaller than b
 * 0 if the fractions are equal
 * 1 if a is larger than b
 */
int compFraction(const Fraction *a, const Fraction *b)
{
    int comp = a->num * b->denom - b->num * a->denom;
    return (0 < comp) - (comp < 0);
}

/* Exercise c: Add values
 * Parameters: two fractions to be added
 * Returns: sum of the fractions
 */
Fraction* addFraction(const Fraction *a, const Fraction *b)
{
    Fraction *sum = setFraction(a->num * b->denom + b->num * a->denom, a->denom * b->denom);
    return sum;
}


/* Reduce fraction
 * Parameters: Fraction to be reduced. Reduction happens on the object itself */
void reduceFraction(Fraction* val)
{
    unsigned int frac_gcd = gcd(val->num, val->denom);
    val->num /= frac_gcd;
    val->denom /= frac_gcd;
}

/* Not needed, but it will be useful to implement this */
void printFraction(const Fraction *val)
{
    printf("%u/%u", val->num, val->denom);
}
