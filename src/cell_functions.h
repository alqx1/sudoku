#ifndef CELL_FUNCTIONS
#define CELL_FUNCTIONS

#include <stdint.h>
#include <stdbool.h>

bool get_note(uint16_t n, uint8_t note_num);
uint16_t get_value(uint16_t n);
bool get_changable(uint16_t n);
void invert_note(uint16_t *n, uint8_t note_num);
void set_note(uint16_t *n, uint8_t note_num, bool is_set);
void set_value(uint16_t *n, uint16_t value);
void set_changable(uint16_t *n, bool changable);

#endif // CELL_FUNCTIONS
