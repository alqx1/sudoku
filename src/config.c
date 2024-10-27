#include "config.h"
#include <stdio.h>
#include <stdlib.h>

struct config read_config(char *file_path) {
    struct config config;

    // default size
    config.window_size = 600;

    FILE *fin = fopen(file_path, "r");

    char buf[32];
    if (fscanf(fin, "%31s", buf) == 1) {
        config.window_size = atoi(buf);
    }

    fclose(fin);
    return config;
}
