#include "sudoku_functions.h"
#include <stdio.h>
#include <stdlib.h>

// solving sudokus
struct cell *read_file(char *path) {
    FILE *fin = fopen(path, "r");
    if (fin == NULL) {
        printf("Error: Can't open file\n");
        exit(2);
    }

    struct cell *sudoku = malloc(sizeof(struct cell) * 81);
    if (sudoku == NULL) {
        printf("Error: Couldn't make board\n");
        exit(3);
    }

    int count = 0;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    while ((read = getline(&line, &len, fin)) != -1 && count < 9) {
        if (read != 10) {
            printf("Error: One line contains too many characters\n");
            exit(5);
        }

        for (size_t i = 0; i < 9; i++) {
            if (line[i] - '0' > 9 || line[i] - '0' < 0) {
                printf("Error: Sudoku contains wrong numbers\n");
                exit(4);
            }
            (sudoku + count * 9 + i)->value = line[i] - '0';
            (sudoku + count * 9 + i)->changable = false;
        }
        count++;
    }

    fclose(fin);
    free(line);
    return sudoku;
}

bool in_row(struct cell *sudoku, const int row, const int num) {
    for (size_t i = 0; i < 9; i++) {
        if ((sudoku + row * 9 + i)->value == num) {
            return true;
        }
    }
    return false;
}

bool in_col(struct cell *sudoku, const int col, const int num) {
    for (size_t i = 0; i < 9; i++) {
        if ((sudoku + i * 9 + col)->value == num) {
            return true;
        }
    }
    return false;
}

bool in_box(struct cell *sudoku, const int x, const int y, const int num) {
    int box_x = x - (x % 3);
    int box_y = y - (y % 3);

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if ((sudoku + (box_y + j) * 9 + box_x + i)->value == num) {
                return true;
            }
        }
    }
    return false;
}

bool find_empty_cell(struct cell *sudoku, int *list) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if ((sudoku + (i * 9) + j)->value == 0) {
                list[0] = j;
                list[1] = i;
                return true;
            }
        }
    }
    return false;
}

bool is_safe(struct cell *sudoku, const int x, const int y, const int num) {
    return (
        !in_row(sudoku, y, num) && !in_col(sudoku, x, num) &&
        !in_box(sudoku, x, y, num));
}

bool solve(struct cell *sudoku) {
    int list[2];

    if (!find_empty_cell(sudoku, list)) {
        return true;
    }

    for (int num = 1; num < 10; num++) {
        if (is_safe(sudoku, list[0], list[1], num)) {
            (sudoku + (list[1] * 9) + list[0])->value = num;

            if (solve(sudoku)) {
                return true;
            }

            (sudoku + (list[1] * 9) + list[0])->value = 0;
        }
    }
    return false;
}

void clear(struct cell *sudoku) {
    for (int i = 0; i < 81; i++) {
        if ((sudoku + i)->changable)
            (sudoku + i)->value = 0;
    }
}

// generate sudoku
struct cell *generate_sudoku(int removed_digits) {
    struct cell *sudoku = generate_diagonal_matrices();
    solve(sudoku);
    remove_n_digits(sudoku, removed_digits);
    return sudoku;
}

struct cell *generate_diagonal_matrices() {
    struct cell *sudoku = malloc(sizeof(struct cell) * 81);
    for (int i = 0; i < 81; i++) {
        (sudoku + i)->value = 0;
        (sudoku + i)->changable = false;
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

void add_nums_to_box(struct cell *sudoku, int box_x, int box_y, int *nums) {
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
            (sudoku + (y + box_y) * 9 + x + box_x)->value = *(nums + y * 3 + x);
        }
    }
}

void remove_n_digits(struct cell *sudoku, int n) {
    while (n != 0) {
        short x = rand() % (9);
        short y = rand() % (9);
        if ((sudoku + y * 9 + x)->value != 0) {
            n--;
            (sudoku + y * 9 + x)->value = 0;
            (sudoku + y * 9 + x)->changable = true;
        }
    }
}

// helper functions
void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

void print_sudoku(struct cell *sudoku) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            printf("%i ", (sudoku + j + 9 * i)->value);
        }
        printf("\n");
    }
}
