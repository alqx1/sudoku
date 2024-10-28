#ifndef GAME
#define GAME

struct pos {
    short x;
    short y;
};

void run(short window_size, struct pos *selected, int *sudoku);

void draw_board(short window_size, struct pos selected, int const *sudoku);
void draw_lines(short window_size);
void draw_selected_box(struct pos selected, short window_size);
void draw_numbers(int const *sudoku, short window_size);

void move_cursor(struct pos* selected);
void place_number(const struct pos selected, int *sudoku);

#endif // GAME
