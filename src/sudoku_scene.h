#ifndef SUDOKU_SCENE
#define SUDOKU_SCENE

#include "pos.h"
#include "config.h"
#include <stdint.h>

// Omogoča spreminanje med vnašanjem dejanskih števk in številk
enum Mode { nums, notes };

// Izvaja delovanje scene (premikanje kazalca, vnašanje vrednosti ...)
void run_sudoku(struct config config, struct pos *selected, uint16_t sudoku[9][9]);

/* Funckije za risanje */
// Nariše celotno mrežo
void draw_board(
    short window_size, struct pos selected, uint16_t const sudoku[9][9]
);
// Naslednje 4 funkcije so pomožne funkcije za risanje mrež
void draw_sudoku_lines(short window_size);
void draw_selected_box(struct pos selected, short window_size);
void draw_numbers(uint16_t const sudoku[9][9], short window_size);
void draw_notes(short window_size, struct pos cell, const bool notes[9]);

/* Funckije za obdelovanje vhoda */
// Premika kazalec glede na trenutni vhod
void move_cursor(struct pos *selected);
// Če je v vhodu številka, jo vnese v trenutno označeno celico
void place_number(const struct pos selected, uint16_t sudoku[9][9]);
/*
 * Posebne funkcije za reševanje, brisanje sudokuja ter spremijanje stanja
 * vnašanja
 */
void sudoku_input(uint16_t sudoku[9][9], uint16_t clear_cells);

#endif // SUDOKU_SCENE
