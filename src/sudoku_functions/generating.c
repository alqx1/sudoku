#include "../cell_functions.h"
#include "../constraints/constraints.h"
#include "sudoku_functions.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

void generate_sudoku(uint16_t sudoku[9][9], int removed_digits) {
    fully_clear(sudoku);
    // Generira diagonalne bloke
    generate_diagonal_matrices(sudoku);

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

void generate_diagonal_matrices(uint16_t sudoku[9][9]) {
    for (size_t i = 0; i < 9; i++) {
        for (size_t j = 0; j < 9; j++) {
            sudoku[i][j] = 0;
        }
    }

    bool random = rand() % 2;

    int nums[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    shuffle_nums(nums);
    add_nums_to_box(sudoku, random ? 0 : 6, 0, nums);

    shuffle_nums(nums);
    add_nums_to_box(sudoku, 3, 3, nums);

    shuffle_nums(nums);
    add_nums_to_box(sudoku, random ? 6 : 0, 6, nums);
}

void shuffle_nums(int nums[9]) {
    int temp;
    for (ssize_t i = 8; i >= 0; i--) {
        short random = rand() % (i + 1);
        temp = nums[random];
        nums[random] = nums[i];
        nums[i] = temp;
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
    int iterations = 100; // Število največ itercij
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
            continue;
        }

        // Spremeni v spremenljivo celico
        set_changable(&sudoku[y][x], true);
        n--;
    }
    return true;
}

// Funkcija podobna kakor "solve" funkcija
void number_of_solutions(uint16_t sudoku[9][9], int *solutions) {
    struct pos empty_cell = {0, 0};

    // Če ne najde prazne celice, je to ena od rešitev,
    // vendar nadaljuje z reševanjem
    if (!find_empty_cell(sudoku, &empty_cell)) {
        *(solutions) += 1;
        return;
    }

    for (int num = 1; num < 10; num++) {
        if (is_safe(sudoku, empty_cell, num)) {
            set_value(&sudoku[empty_cell.y][empty_cell.x], num);

            number_of_solutions(sudoku, solutions);

            set_value(&sudoku[empty_cell.y][empty_cell.x], 0);
        }
    }
}
