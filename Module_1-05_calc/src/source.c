#include <stdio.h>
#include <math.h>
#include "source.h"
 
 
 
void simple_sum(void)
{
    int a, b;
    scanf("%d %d", &a, &b);
    printf("%d + %d = %d\n", a, b, a + b);
}
 
 
void simple_math(void)
{
    float a, b;
    char o;
    scanf("%f %c %f", &a, &o, &b);
    switch(o) {
        case '+':
            printf("%.1f", a + b);
            break;
        case '-':
            printf("%.1f", a - b);
            break;
        case '*':
            printf("%.1f", a * b);
            break;
        case '/':
            printf("%.1f", a / b);
            break;
        default:
            printf("ERR");
    }
}