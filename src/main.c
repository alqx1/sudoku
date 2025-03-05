#include "game.h"

int main(int argc, char **argv) {
    game_t game;

    // Inicializiramo vse
    init(&game, argc, argv);

    // Začnemo delovanje programa
    run(&game);

    // Končamo delovanje
    clean(&game);
}
