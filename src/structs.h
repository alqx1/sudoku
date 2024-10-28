#ifndef STRUCTS
#define STRUCTS

#include <stdbool.h>

struct pos {
    short x;
    short y;
};

struct cell {
    int value;
    bool changable;
};

#endif // STRUCTS
