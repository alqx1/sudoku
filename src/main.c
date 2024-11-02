#include "config.h"
#include "game.h"
#include "sudoku_functions.h"
#include <raylib.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct config config;
struct pos selected;
uint16_t sudoku[9][9];

int main(int argc, char **argv) {
    srand(time(NULL));
    config = read_config("./config.txt");
    if (argc == 1) {
        generate_sudoku(sudoku, 55);
    }
    else {
        printf("Error: Too many arguments\n");
        printf("Usage: (executable)\n");
        exit(EXIT_FAILURE);
    }

    selected.x = 4;
    selected.y = 4;

    print_sudoku(sudoku);

    InitWindow(config.window_size, config.window_size, "Sudoku");
    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        run(config.window_size, &selected, sudoku);

        EndDrawing();
    }

    CloseWindow();
}
