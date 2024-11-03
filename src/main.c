#include "config.h"
#include "game.h"
#include "sudoku_functions.h"
#include <raylib.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct config config;
struct pos cursor;
uint16_t sudoku[9][9];

int main(int argc, char **argv) {
    srand(time(NULL));
    config = read_config("./config.txt");

    if (argc == 1) {
        // generates and stores into sudoku
        generate_sudoku(sudoku, config.clear_cells);
    }
    else {
        printf("Error: Too many arguments\n");
        printf("Usage: (executable)\n");
        exit(EXIT_FAILURE);
    }

    // default placement of cursor
    cursor.x = 4;
    cursor.y = 4;

    InitWindow(config.window_size, config.window_size, "Sudoku");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        run(config.window_size, &cursor, sudoku);

        EndDrawing();
    }

    CloseWindow();
}
