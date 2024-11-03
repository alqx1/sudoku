#ifndef SUDOKU_SCENE
#define SUDOKU_SCENE

#include "pos.h"
#include <stdint.h>

enum Mode { nums, notes };

void run_sudoku(short window_size, struct pos *selected, uint16_t sudoku[9][9]);

void draw_board(
    short window_size, struct pos selected, uint16_t const sudoku[9][9]);
void draw_sudoku_lines(short window_size);
void draw_selected_box(struct pos selected, short window_size);
void draw_numbers(uint16_t const sudoku[9][9], short window_size);
void draw_notes(short window_size, struct pos cell, const bool notes[9]);

void move_cursor(struct pos *selected);
void place_number(const struct pos selected, uint16_t sudoku[9][9]);
void sudoku_input(uint16_t sudoku[9][9]);

#endif // SUDOKU_SCENE
