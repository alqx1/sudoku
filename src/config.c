#include "config.h"
#include <stdio.h>
#include <stdlib.h>

struct config read_config(char *file_path) {
    FILE *fin = fopen(file_path, "r");
    struct config config;
    char buf[32];

    // default size
    config.window_size = 600;
    if (fscanf(fin, "%31s", buf) == 1) {
        config.window_size = atoi(buf);
    }

    if (fscanf(fin, "%31s", buf) == 1) {
        config.clear_cells = atoi(buf);
    }

    fclose(fin);
    return config;
}
