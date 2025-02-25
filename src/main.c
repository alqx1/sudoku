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
    // Prebere konfiguracijo in jo shrani v spremenljivko
    config = read_config("./config.txt");

    // Preverjanje argumentov
    if (argc == 1) {
        // Generira sudoku mrežo in jo shrani v tabelo
        generate_sudoku(sudoku, config.clear_cells);
    }
    // Če je preveč argumentov, izhod iz programa
    else {
        printf("Error: Too many arguments\n");
        printf("Usage: (executable)\n");
        exit(EXIT_FAILURE);
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
