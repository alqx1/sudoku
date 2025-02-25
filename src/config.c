#include "config.h"
#include <stdio.h>
#include <stdlib.h>

struct config read_config(char *file_path) {
    // Odpre datoteko za branje
    FILE *fin = fopen(file_path, "r");

    struct config config;

    char buf[32]; // Za začasno shranjevanje datotečnega vhoda

    // Prevzeta vrednost
    config.window_size = 600;
    if (fscanf(fin, "%31s", buf) == 1) {
        config.window_size = atoi(buf);
    }

    if (fscanf(fin, "%31s", buf) == 1) {
        config.clear_cells = atoi(buf);
    }

    // Zapre datoteko
    fclose(fin);
    return config;
}
