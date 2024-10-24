#ifndef GENERATOR
#define GENERATOR

int *generate_sudoku(int removed_digits);

int *generate_diagonal_matrices();
void shuffle_nums(int *nums);
void add_nums_to_box(int *sudoku, int box_x, int box_y, int *nums);
void remove_n_digits(int *sudoku, int n);
void swap(int *x, int *y);

#endif // GENERATOR
