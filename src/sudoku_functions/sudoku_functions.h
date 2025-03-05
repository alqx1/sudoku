#ifndef SUDOKU_FUNCTIONS
#define SUDOKU_FUNCTIONS

#include "../pos.h"
#include <stdbool.h>
#include <stdint.h>

// Prebere iz datoteke in zapiše v tabelo
bool read_file(uint16_t sudoku[9][9], char *path);

// Vrne, če najde prazno celico in jo zapiše v "position"
bool find_empty_cell(uint16_t sudoku[9][9], struct pos *position);

// Reši sudoku, če je rešitev
bool solve(uint16_t sudoku[9][9]);

// Preveri, če je neka števka validna v celici
bool is_safe(uint16_t sudoku[9][9], const struct pos position, const int num);

// Sprazni vse spremenljive celice
void clear(uint16_t sudoku[9][9]);
// Sprazni vse celice
void fully_clear(uint16_t sudoku[9][9]);

// Zgenerira sudoku poln sudoku, zbriše nekaj številk in zapiše v tabelo
void generate_sudoku(uint16_t sudoku[9][9], int removed_digits);

void print_sudoku(uint16_t sudoku[9][9]);

// Kopira sudoku v novo tabelo
void copy_sudoku(uint16_t const original_sudoku[9][9], uint16_t copy[9][9]);

// Enako kot "solve" funkcija vendar zapiše še število rešitev v spremenljivko
void number_of_solutions(uint16_t sudoku[9][9], int *solutions);

#endif // SUDOKU_FUNCTIONS
