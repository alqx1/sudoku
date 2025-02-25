#ifndef GAME
#define GAME

#include "pos.h"
#include "config.h"
#include <stdint.h>

// Enumerator namenjen shranjevaju trenutnega stanja programa
// (Potreben v primeru dodajanja več scen)
enum Scene { s_sudoku };

/* 
 * Izvede delovanje programa
 * (premikanje kazalca, vstavljanje vrednosti...)
 */
void run(struct config config, struct pos *selected, uint16_t sudoku[9][9]);

#endif // GAME
