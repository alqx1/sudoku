#include "sudoku_functions.h"
#include "../cell_functions.h"
#include <stdio.h>
#include <stdlib.h>

bool read_file(uint16_t sudoku[9][9], char *path) {
    fully_clear(sudoku);

    FILE *fin = fopen(path, "r");
    if (fin == NULL) {
        fprintf(stderr, "Error: Can't open file\n");
        return false;
    }

    int count = 0;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    while ((read = getline(&line, &len, fin)) != -1 && count < 1) {
        if (read != 82) {
            fprintf(
                stderr, "Error: Line contains too many/little characters\n"
            );
            free(line);
            fclose(fin);
            return false;
        }

        for (size_t i = 0; i < 9; i++) {
            for (size_t j = 0; j < 9; j++) {
                if (line[i * 9 + j] > '9' || line[i * 9 + j] < '0') {
                    fprintf(stderr, "Error: Sudoku contains wrong numbers\n");
                    free(line);
                    fclose(fin);
                    return false;
                }
                sudoku[i][j] = 0;
                set_value(&sudoku[i][j], line[i * 9 + j] - '0');
                set_changable(&sudoku[i][j], (line[i * 9 + j] - '0' == 0));
            }
        }
        count++;
    }

    fclose(fin);
    free(line);

    return true;
}

void clear(uint16_t sudoku[9][9]) {
    // Vsako vrednost v spremljivi celici odstrani
    for (size_t i = 0; i < 9; i++) {
        for (size_t j = 0; j < 9; j++) {
            if (get_changable(sudoku[i][j])) {
                sudoku[i][j] = 0;
                set_changable(&sudoku[i][j], true);
            }
        }
    }
}

void fully_clear(uint16_t sudoku[9][9]) {
    // Vsako vrednost v celici odstrani
    for (size_t i = 0; i < 9; i++) {
        for (size_t j = 0; j < 9; j++) {
            sudoku[i][j] = 0;
        }
    }
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
