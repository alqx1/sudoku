#include "cell_functions.h"

bool get_note(uint16_t n, uint8_t note_num) {
    n >>= note_num;
    n &= 1;
    return n;
}

uint16_t get_value(uint16_t n) {
    n >>= 10;
    return n;
}

bool get_changable(uint16_t n) { return n & 1; }

void invert_note(uint16_t *n, uint8_t note_num) { *n ^= (1 << note_num); }

void set_note(uint16_t *n, uint8_t note_num, bool is_set) {
    if (is_set) {
        *n |= (1 << note_num);
        return;
    }
    *n &= ~(1 << note_num);
}

void set_value(uint16_t *n, uint16_t value) {
    uint16_t mask = ~0;
    mask >>= 6;
    *n &= mask;
    value <<= sizeof(uint16_t) * 8 - 2 - 4;
    *n += value;
}

void set_changable(uint16_t *n, bool changable) {
    if (changable) {
        *n |= 1;
        return;
    }
    *n &= ~1;
}
