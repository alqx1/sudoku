#ifndef CONFIG
#define CONFIG

#include <stdint.h>

struct config {
    uint16_t window_size;
    uint8_t clear_cells;
};

// reads everything from config.txt to config struct
struct config read_config(char *file_path);

#endif // CONFIG
