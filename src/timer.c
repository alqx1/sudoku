#include "timer.h"
#include "cell_functions.h"
#include "constraints/constraints.h"
#include "sudoku_functions/sudoku_functions.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

double time_backtrack(uint16_t sudoku[9][9]);
double time_constraint(uint16_t sudoku[9][9]);
void line_into_sudoku(char *line, uint16_t sudoku[9][9]);

void time_sudokus_in_file(char *filename) {
    uint16_t sudoku[9][9];
    FILE *fin = fopen(filename, "r");
    if (fin == NULL) {
        fprintf(stderr, "Error: Can't open file\n");
        return;
    }

    int count = 0;
    char line[256];

    double sum = 0;
    while (fgets(line, sizeof(line), fin) != NULL) {
        if (strlen(line) != 82) {
            fprintf(
                stderr, "Error: Line contains too many/little characters\n"
            );
            fclose(fin);
            break;
        }

        for (int i = 0; i < 81; i++) {
            if (line[i] > '9' || line[i] < '0') {
                fprintf(stderr, "Error: Sudoku contains wrong numbers\n");
                fclose(fin);
                break;
            }
        }

        line_into_sudoku(line, sudoku);
        double temp = time_constraint(sudoku);
        sum += temp;
        printf("num %i: %.10f\n", count + 1, temp);

        count++;
    }

    printf("average: %.10f\n", sum / count);
    printf("count: %i\n", count);

    fclose(fin);
}

void line_into_sudoku(char *line, uint16_t sudoku[9][9]) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            sudoku[i][j] = 0;
            set_value(&sudoku[i][j], line[i * 9 + j] - '0');
            set_changable(&sudoku[i][j], (line[i * 9 + j] - '0' == 0));
        }
    }
}


double time_backtrack(uint16_t sudoku[9][9]) {
    uint16_t copy[9][9];
    copy_sudoku(sudoku, copy);

    clock_t start = clock();
    solve(copy);
    clock_t stop = clock();

    double diff = (double)(stop - start) / CLOCKS_PER_SEC;
    return diff;
}

double time_constraint(uint16_t sudoku[9][9]) {
    uint16_t copy[9][9];
    copy_sudoku(sudoku, copy);

    clock_t start = clock();
    constrain(copy);
    solve(copy);
    clock_t stop = clock();

    double diff = (double)(stop - start) / CLOCKS_PER_SEC;
    return diff;
}
