#include "sudoku_functions.h"
#include "cell_functions.h"
#include <stdio.h>
#include <stdlib.h>

// solving sudokus
void read_file(uint16_t sudoku[9][9], char *path) {
    FILE *fin = fopen(path, "r");
    if (fin == NULL) {
        printf("Error: Can't open file\n");
        free(fin);
        exit(2);
    }

    int count = 0;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    while ((read = getline(&line, &len, fin)) != -1 && count < 9) {
        if (read != 10) {
            printf("Error: One line contains too many characters\n");
            free(fin);
            free(line);
            exit(5);
        }

        for (size_t i = 0; i < 9; i++) {
            if (line[i] - '0' > 9 || line[i] - '0' < 0) {
                printf("Error: Sudoku contains wrong numbers\n");
                free(fin);
                free(line);
                exit(4);
            }

            sudoku[count][i] = 0;
            set_value(&sudoku[count][i], line[i] - '0');
            set_changable(&sudoku[count][i], false);
        }
        count++;
    }

    fclose(fin);
    free(line);
}

bool in_row(uint16_t sudoku[9][9], const int row, const int num) {
    for (size_t i = 0; i < 9; i++) {
        if (get_value(sudoku[row][i]) == num) {
            return true;
        }
    }
    return false;
}

bool in_col(uint16_t sudoku[9][9], const int col, const int num) {
    for (size_t i = 0; i < 9; i++) {
        if (get_value(sudoku[i][col]) == num) {
            return true;
        }
    }
    return false;
}

bool in_box(uint16_t sudoku[9][9], const struct pos position, const int num) {
    int box_x = position.x - (position.x % 3);
    int box_y = position.y - (position.y % 3);

    for (size_t i = 0; i < 3; i++) {
        for (size_t j = 0; j < 3; j++) {
            if (get_value(sudoku[box_y + i][box_x + j]) == num) {
                return true;
            }
        }
    }
    return false;
}

bool find_empty_cell(uint16_t sudoku[9][9], struct pos *position) {
    for (size_t i = 0; i < 9; i++) {
        for (size_t j = 0; j < 9; j++) {
            if (get_value(sudoku[i][j]) == 0) {
                position->y = i;
                position->x = j;
                return true;
            }
        }
    }
    return false;
}

bool is_safe(uint16_t sudoku[9][9], const struct pos position, const int num) {
    return (
        !in_row(sudoku, position.y, num) && !in_col(sudoku, position.x, num) &&
        !in_box(sudoku, position, num));
}

bool solve(uint16_t sudoku[9][9]) {
    struct pos empty_cell = {0, 0};

    if (!find_empty_cell(sudoku, &empty_cell)) {
        return true;
    }

    for (int num = 1; num < 10; num++) {
        if (is_safe(sudoku, empty_cell, num)) {
            set_value(&sudoku[empty_cell.y][empty_cell.x], num);

            if (solve(sudoku)) {
                return true;
            }

            set_value(&sudoku[empty_cell.y][empty_cell.x], 0);
        }
    }
    return false;
}

void clear(uint16_t sudoku[9][9]) {
    for (size_t i = 0; i < 9; i++) {
        for (size_t j = 0; j < 9; j++) {
            if (get_changable(sudoku[i][j])) {
                set_value(&sudoku[i][j], 0);
            }
        }
    }
}

// generate sudoku
void generate_sudoku(uint16_t sudoku[9][9], int removed_digits) {
    generate_diagonal_matrices(sudoku);
    solve(sudoku);

    uint16_t copy[9][9];
    copy_sudoku(sudoku, copy);
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

    int nums[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    shuffle_nums(nums);
    add_nums_to_box(sudoku, 0, 0, nums);

    shuffle_nums(nums);
    add_nums_to_box(sudoku, 3, 3, nums);

    shuffle_nums(nums);
    add_nums_to_box(sudoku, 6, 6, nums);
}

void shuffle_nums(int nums[9]) {
    for (ssize_t i = 8; i >= 0; i--) {
        short random = rand() % (i + 1);
        swap(nums + random, nums + i);
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
    int iterations = 50000;
    while (n != 0) {
        if (iterations == 0)
            return false;

        short x = rand() % 9;
        short y = rand() % 9;

        if ((temp = get_value(sudoku[y][x])) == 0) {
            continue;
        }

        set_value(&sudoku[y][x], 0);

        solutions = 0;
        number_of_solutions(sudoku, &solutions);
        if (solutions != 1) {
            set_value(&sudoku[y][x], temp);
            continue;
        }

        set_changable(&sudoku[y][x], true);
        n--;
    }
    return true;
}

// helper functions
void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

void print_sudoku(uint16_t sudoku[9][9]) {
    for (size_t i = 0; i < 9; i++) {
        for (size_t j = 0; j < 9; j++) {
            printf("%i ", get_value(sudoku[i][j]));
        }
        printf("\n");
    }
}

void copy_sudoku(uint16_t const original_sudoku[9][9], uint16_t copy[9][9]) {
    for (size_t i = 0; i < 9; i++) {
        for (size_t j = 0; j < 9; j++) {
            copy[i][j] = original_sudoku[i][j];
        }
    }
}

bool number_of_solutions(uint16_t sudoku[9][9], int *solutions) {
    struct pos empty_cell = {0, 0};

    if (!find_empty_cell(sudoku, &empty_cell)) {
        *(solutions) = *(solutions) + 1;
        return false;
    }

    for (int num = 1; num < 10; num++) {
        if (is_safe(sudoku, empty_cell, num)) {
            set_value(&sudoku[empty_cell.y][empty_cell.x], num);

            number_of_solutions(sudoku, solutions);

            set_value(&sudoku[empty_cell.y][empty_cell.x], 0);
        }
    }
    return false;
}
