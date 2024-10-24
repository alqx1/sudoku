#include "solver.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: ./executable [sudoku_name]\n")
        exit(1);
    }

    int *sudoku = read_file(argv[1]);

    solve(sudoku);
    print_sudoku(sudoku);

    free(sudoku);
}
