#include "../cell_functions.h"
#include "../constraints/constraints.h"
#include "sudoku_functions.h"
#include <stddef.h>
#include <stdlib.h>

void generate_boxes(uint16_t sudoku[9][9]);
void shuffle_nums(int *nums, int n);
void add_nums_to_box(uint16_t sudoku[9][9], int box_x, int box_y, int nums[9]);
bool remove_n_digits(uint16_t sudoku[9][9], int n);

void generate_sudoku(uint16_t sudoku[9][9], int removed_digits) {
    fully_clear(sudoku);

    generate_boxes(sudoku);
    // Reši sudoku do konca
    constrain(sudoku);
    solve(sudoku);

    // Ustvarimo kopijo, če pri odstranjevanju pride do napake
    uint16_t copy[9][9];
    copy_sudoku(sudoku, copy);
    // Če pri odstranjevanju pride do napake, kopiraj originalno tabelo nazaj
    while (!remove_n_digits(sudoku, removed_digits)) {
        copy_sudoku(copy, sudoku);
    }
}

void generate_boxes(uint16_t sudoku[9][9]) {
    int boxy_pos[3] = {0, 3, 6};
    shuffle_nums(boxy_pos, 3);

    int nums[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    shuffle_nums(nums, 9);
    add_nums_to_box(sudoku, 0, boxy_pos[0], nums);

    shuffle_nums(nums, 9);
    add_nums_to_box(sudoku, 3, boxy_pos[1], nums);

    shuffle_nums(nums, 9);
    add_nums_to_box(sudoku, 6, boxy_pos[2], nums);
}

void shuffle_nums(int *nums, int n) {
    int temp;
    for (ssize_t i = n - 1; i >= 0; i--) {
        short random = rand() % (i + 1);
        int temp = nums[i];
        nums[i] = nums[random];
        nums[random] = temp;
    }
}

void add_nums_to_box(uint16_t sudoku[9][9], int box_x, int box_y, int nums[9]) {
    for (size_t y = 0; y < 3; y++) {
        for (size_t x = 0; x < 3; x++) {
            set_value(&sudoku[box_y + y][box_x + x], nums[y * 3 + x]);
        }
    }
}

bool remove_n_digits(uint16_t sudoku[9][9], int n) {
    int temp;
    int solutions;
    int iterations = n * 2; // Število največ itercij
    while (n != 0) {
        // Če se kdaj rekurzija zatakne
        if (iterations == 0)
            return false;

        // Generira naključno pozicijo
        short x = rand() % 9;
        short y = rand() % 9;

        while ((temp = get_value(sudoku[y][x])) == 0) {
            x = rand() % 9;
            y = rand() % 9;
            continue;
        }

        set_value(&sudoku[y][x], 0);

        // Preveri število rešitev, če ni samo ena rešitev, poskusi drugo celico
        solutions = 0;
        number_of_solutions(sudoku, &solutions);
        if (solutions != 1) {
            set_value(&sudoku[y][x], temp);
            iterations--;
            continue;
        }

        // Spremeni v spremenljivo celico
        set_changable(&sudoku[y][x], true);
        n--;
    }
    return true;
}
