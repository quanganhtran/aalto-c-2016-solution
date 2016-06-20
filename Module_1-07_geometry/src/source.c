#include <stdio.h>
#include <math.h>
#include "source.h"
 
 
void multi_table(unsigned int xsize, unsigned int ysize)
{
    for (int y = 1; y <= ysize; y++) {
        for (int x = 1; x <= xsize; x++) {
            printf("%4d", x * y);
        }
        printf("\n");
    }
}
 
 
void draw_triangle(unsigned int size)
{
    for (int i = size; i > 0; i--) {
        for (int j = 1; j <= size; j++) {
            if (j < i) printf(".");
            else printf("#");
        }
        printf("\n");
    }
}
 
double distance(int x, int y)
{
    return sqrt(x * x + y * y);
}
 
 
void draw_ball(unsigned int radius)
{
    for (int y = 0; y < radius * 2 + 1; y++) {
        for (int x = 0; x < radius * 2 + 1; x++) {
            if (distance(x - radius, y - radius) <= radius) printf("*");
            else printf(".");
        }
        printf("\n");
    }
}