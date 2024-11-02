#ifndef GAME
#define GAME

#include "structs.h"
#include <stdint.h>

void run(short window_size, struct pos *selected, uint16_t sudoku[9][9]);

void draw_board(
    short window_size, struct pos selected, uint16_t const sudoku[9][9]);
void draw_lines(short window_size);
void draw_selected_box(struct pos selected, short window_size);
void draw_numbers(uint16_t const sudoku[9][9], short window_size);
void draw_notes(short window_size, struct pos cell, const bool notes[9]);

void move_cursor(struct pos *selected);
void place_number(const struct pos selected, uint16_t sudoku[9][9]);
void input(uint16_t sudoku[9][9]);

#endif // GAME
