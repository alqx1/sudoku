#ifndef CONFIG
#define CONFIG

/*
* Structura je namenjena shranjevanju podatkov iz config.txt
*/

#include <stdint.h>

struct config {
    uint16_t window_size; // širina in višina okna
    uint8_t clear_cells; // koliko celic je praznih
};

// Prebere "config" datoteko in vrne strukturo config
struct config read_config(char *file_path);

#endif // CONFIG
