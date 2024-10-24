#include "generator.h"
#include "solver.h"
#include <stdlib.h>

int *generate_sudoku(int removed_digits) {
    int* sudoku = generate_diagonal_matrices();
    solve(sudoku);
    remove_n_digits(sudoku, removed_digits);
    return sudoku;
}

int *generate_diagonal_matrices() {
    int *sudoku = malloc(sizeof(int) * 81);
    for (int i = 0; i < 81; i++) {
        *(sudoku + i) = 0;
    }

    int nums[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    shuffle_nums(nums);
    add_nums_to_box(sudoku, 0, 0, nums);

    shuffle_nums(nums);
    add_nums_to_box(sudoku, 3, 3, nums);

    shuffle_nums(nums);
    add_nums_to_box(sudoku, 6, 6, nums);

    return sudoku;
}

void shuffle_nums(int *nums) {
    for (int i = 8; i >= 0; i--) {
        short random = rand() % (i + 1);
        swap(nums + random, nums + i);
    }
}

void add_nums_to_box(int *sudoku, int box_x, int box_y, int *nums) {
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
            *(sudoku + (y + box_y) * 9 + x + box_x) = *(nums + y * 3 + x);
        }
    }
}

void remove_n_digits(int *sudoku, int n) {
    while (n != 0) {
        short x = rand() % (9);
        short y = rand() % (9);
        if (*(sudoku + y * 9 + x) != 0) {
            n--;
            *(sudoku + y * 9 + x) = 0;
        }
    }
}

void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}
