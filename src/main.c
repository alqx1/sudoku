#include "config.h"
#include "game.h"
#include "sudoku_functions/sudoku_functions.h"
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct config config;
struct pos cursor;
uint16_t sudoku[9][9];

int main(int argc, char **argv) {
    srand(time(NULL));
    // Prebere konfiguracijo in jo shrani v spremenljivko
    config = read_config("./config.txt");


    bool read = false;
    // Preverjanje argumentov
    if (argc == 1) {
        read = read_file(sudoku, "sudoku.txt");
    }
    else if (argc == 2) {
        read = read_file(sudoku, argv[1]);
    }
    // Če je preveč argumentov, izhod iz programa
    else {
        printf("Error: Too many arguments\n");
        printf("Usage: (executable)\n");
        exit(EXIT_FAILURE);
    }

    if (!read) {
        generate_sudoku(sudoku, config.clear_cells);
    }

    // Postavi kazalec na sredino tabele
    cursor.x = 4;
    cursor.y = 4;

    // Pripravi okno
    InitWindow(config.window_size, config.window_size, "Sudoku");
    SetTargetFPS(60);

    // Ko je okno še odprto
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Izvede program
        run(config, &cursor, sudoku);

        EndDrawing();
    }

    // Dokončno zapre okno
    CloseWindow();
}
