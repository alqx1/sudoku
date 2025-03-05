#include "game.h"
#include "sudoku_functions/sudoku_functions.h"
#include "sudoku_scene.h"

#include <raylib.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void init(game_t *game, int argc, char **argv) {
    srand(time(NULL));
    // Prebere konfiguracijo in jo shrani v spremenljivko
    game->config = read_config("./config.txt");

    bool read = false;
    // Preverjanje argumentov
    if (argc == 1) {
        read = read_file(game->sudoku, "sudoku.txt");
    }
    else if (argc == 2) {
        read = read_file(game->sudoku, argv[1]);
    }
    // Če je preveč argumentov, izhod iz programa
    else {
        fprintf(stderr, "Error: Too many arguments\n");
        printf("Usage: (executable)\n");
        exit(EXIT_FAILURE);
    }

    if (!read) {
        generate_sudoku(game->sudoku, game->config.clear_cells);
    }

    // Postavi kazalec na sredino tabele
    game->cursor.x = 4;
    game->cursor.y = 4;

    // Pripravi okno
    SetTraceLogLevel(LOG_ERROR);
    SetTargetFPS(60);
    InitWindow(game->config.window_size, game->config.window_size, "Sudoku");
}

void run(game_t *game) {
    // Ko je okno še odprto
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Izvede program
        update_sudoku(game->config, &game->cursor, game->sudoku);
        draw_board(game->config.window_size, game->cursor, game->sudoku);

        EndDrawing();
    }
}

void clean(game_t *game) {
    CloseWindow();
}
