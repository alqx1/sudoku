#include "solver.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int *read_file(char *path) {
    FILE *fin = fopen(path, "r");
    if (fin == NULL) {
        printf("Error: Can't open file\n");
        exit(2);
    }

    int *sudoku = malloc(sizeof(int) * 81);
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
            *(sudoku + count * 9 + i) = line[i] - '0';
        }
        count++;
    }

    fclose(fin);
    free(line);
    return sudoku;
}

void print_sudoku(int *sudoku) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            printf("%i ", *(sudoku + j + 9 * i));
        }
        printf("\n");
    }
}

bool in_row(int *sudoku, const int row, const int num) {
    for (size_t i = 0; i < 9; i++) {
        if (*(sudoku + row * 9 + i) == num) {
            return true;
        }
    }
    return false;
}

bool in_col(int *sudoku, const int col, const int num) {
    for (size_t i = 0; i < 9; i++) {
        if (*(sudoku + i * 9 + col) == num) {
            return true;
        }
    }
    return false;
}

bool in_box(int *sudoku, const int x, const int y, const int num) {
    int box_x = x - (x % 3);
    int box_y = y - (y % 3);

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (*(sudoku + (box_y + j) * 9 + box_x + i) == num) {
                return true;
            }
        }
    }
    return false;
}

bool find_empty_cell(int *sudoku, int *list) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (*(sudoku + (i * 9) + j) == 0) {
                list[0] = j;
                list[1] = i;
                return true;
            }
        }
    }
    return false;
}

bool is_safe(int *sudoku, const int x, const int y, const int num) {
    return (
        !in_row(sudoku, y, num) && !in_col(sudoku, x, num) &&
        !in_box(sudoku, x, y, num));
}

bool solve(int *sudoku) {
    int list[2];

    if (!find_empty_cell(sudoku, list)) {
        return true;
    }

    for (int num = 1; num < 10; num++) {
        if (is_safe(sudoku, list[0], list[1], num)) {
            *(sudoku + (list[1] * 9) + list[0]) = num;

            if (solve(sudoku)) {
                return true;
            }

            *(sudoku + (list[1] * 9) + list[0]) = 0;
        }
    }
    return false;
}
