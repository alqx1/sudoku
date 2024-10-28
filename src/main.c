#include "config.h"
#include "game.h"
#include "sudoku_functions.h"
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct config config;
struct pos selected;

int main(int argc, char **argv) {
    srand(time(NULL));
    config = read_config("./config.txt");

    selected.x = 4;
    selected.y = 4;

    struct cell *sudoku = generate_sudoku(60);

    InitWindow(config.window_size, config.window_size, "Sudoku");
    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        run(config.window_size, &selected, sudoku);

        EndDrawing();
    }

    CloseWindow();

    free(sudoku);
}
