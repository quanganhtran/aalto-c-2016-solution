#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "gameoflife.h"


State** initCells(unsigned int xsize, unsigned int ysize) {
    State** cells = calloc(ysize, sizeof(*cells));
    for (unsigned int i = 0; i < ysize; i++) {
        cells[i] = calloc(xsize, sizeof(**cells));
    }
    return cells;
}

void releaseCells(State** cells, unsigned int ysize) {
    for (unsigned int y = 0; y < ysize; y++) {
        free(cells[y]);
    }
    free(cells);
}

/* Exercise a: Allocates needed memory for the field structure and
 * the actual game field. 'xsize' and 'ysize' indicate the horizontal and
 * vertical dimensions of the field.
 * 
 * Returns: pointer to the Field structure allocated by this function.
 */
Field *createField(unsigned int xsize, unsigned int ysize)
{
    Field* field = malloc(sizeof(Field));
    field->xsize = xsize;
    field->ysize = ysize;
    field->cells = initCells(xsize, ysize);
    return field;
}

/* Free memory allocated for field <f>.
 */
void releaseField(Field *f)
{
    releaseCells(f->cells, f->ysize);
    free(f);
}

/* Exercise b: Initialize game field by setting exactly <n> cells into
 * ALIVE state in the game field <f>.
 */
void initField(Field *f, unsigned int n)
{
    unsigned int total = f->xsize * f->ysize;
    for (unsigned int i = 0; i < total; i++) {
        if (rand() % (total - i) < n) {
            f->cells[i / f->xsize][i % f->xsize] = ALIVE;
            n--;
            if (n <= 0)
                return;
        }
    }
    exit(EXIT_FAILURE);
}

/* Exercise c: Output the current state of field <f>.
 */
void printField(const Field *f)
{
    for (unsigned int y = 0; y < f->ysize; y++) {
        for (unsigned int x = 0; x < f->xsize; x++) {
            printf("%c", f->cells[y][x] == ALIVE ? '*' : '.');
        }
        printf("\n");
    }
}


/* Exercise d: Advance field <f> by one generation.
 */
void tick(Field *f)
{
    State** cells = f->cells;
    State** stateAfter = initCells(f->xsize, f->ysize);
    for (unsigned int y = 0; y < f->ysize; y++) {
        for (unsigned int x = 0; x < f->xsize; x++) {
            // Count neighbors
            int neighbors = 0;
            if (y > 0) {
                neighbors += cells[y - 1][x] == ALIVE;
                if (x > 0) {
                    neighbors += cells[y - 1][x - 1] == ALIVE;
                }
                if (x < f->xsize - 1) {
                    neighbors += cells[y - 1][x + 1] == ALIVE;
                }
            }
            if (y < f->ysize - 1) {
                neighbors += cells[y + 1][x] == ALIVE;
                if (x > 0) {
                    neighbors += cells[y + 1][x - 1] == ALIVE;
                }
                if (x < f->xsize - 1) {
                    neighbors += cells[y + 1][x + 1] == ALIVE;
                }
            }
            if (x > 0) {
                neighbors += cells[y][x - 1] == ALIVE;
            }
            if (x < f->xsize - 1) {
                neighbors += cells[y][x + 1] == ALIVE;
            }
            // Apply rules
            if (cells[y][x] == ALIVE) {
                stateAfter[y][x] = (2 <= neighbors && neighbors <= 3) ? ALIVE : DEAD;
            } else {
                stateAfter[y][x] = (neighbors == 3) ? ALIVE : DEAD;
            }
        }
    }
    releaseCells(f->cells, f->ysize);
    f->cells = stateAfter;
}