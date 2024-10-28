#ifndef GAME
#define GAME

#include "structs.h"

void run(short window_size, struct pos *selected, struct cell *sudoku);

void draw_board(short window_size, struct pos selected, struct cell const *sudoku);
void draw_lines(short window_size);
void draw_selected_box(struct pos selected, short window_size);
void draw_numbers(struct cell const *sudoku, short window_size);

void move_cursor(struct pos *selected);
void place_number(const struct pos selected, struct cell *sudoku);
void input(struct cell *sudoku);

#endif // GAME
