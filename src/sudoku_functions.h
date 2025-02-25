#ifndef SUDOKU_FUNCTIONS
#define SUDOKU_FUNCTIONS

#include "pos.h"
#include <stdbool.h>
#include <stdint.h>

// Prebere iz datoteke in zapiše v tabelo
void read_file(uint16_t sudoku[9][9], char *path);

// Preveri, če je neka števka že v vrstici/stolpcu/bloku
bool in_row(uint16_t sudoku[9][9], const int row, const int num);
bool in_col(uint16_t sudoku[9][9], const int col, const int num);
bool in_box(uint16_t sudoku[9][9], const struct pos position, const int num);
bool is_safe(uint16_t sudoku[9][9], const struct pos position, const int num);

// Vrne, če najde prazno celico in jo zapiše v "position"
bool find_empty_cell(uint16_t sudoku[9][9], struct pos *position);

// Reši sudoku, če je rešitev
bool solve(uint16_t sudoku[9][9]);

// Sprazni vse spremenljive celice
void clear(uint16_t sudoku[9][9]);
// Sprazni vse celice
void clear_all(uint16_t sudoku[9][9]);

// Zgenerira sudoku poln sudoku, zbriše nekaj številk in zapiše v tabelo
void generate_sudoku(uint16_t sudoku[9][9], int removed_digits);
// Zgenerira naključne bloke po naključni diagonali
void generate_diagonal_matrices(uint16_t sudoku[9][9]);
// Zmeša tabelo številk
void shuffle_nums(int nums[9]);
// Doda številke iz tabele v določen blok
void add_nums_to_box(uint16_t sudoku[9][9], int box_x, int box_y, int nums[9]);
// Odstrani n številk iz sudokuja
bool remove_n_digits(uint16_t sudoku[9][9], int n);

void swap(int *x, int *y); // Zamenja dve številki
void print_sudoku(uint16_t sudoku[9][9]);

// Kopira sudoku v novo tabelo
void copy_sudoku(uint16_t const original_sudoku[9][9], uint16_t copy[9][9]);

// Enako kot "solve" funkcija vendar zapiše še število rešitev v spremenljivko
void number_of_solutions(uint16_t sudoku[9][9], int *solutions);

#endif // SUDOKU_FUNCTIONS
