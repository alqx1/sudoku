#include "stdbool.h"

int *read_file(char *path);
void print_sudoku(int *sudoku);
bool in_row(int *sudoku, const int row, const int num);
bool in_col(int *sudoku, const int col, const int num);
bool in_box(int *sudoku, const int x, const int y, const int num);
bool is_safe(int *sudoku, const int x, const int y, const int num);
bool find_empty_cell(int *sudoku, int *list);
bool solve(int *sudoku);
