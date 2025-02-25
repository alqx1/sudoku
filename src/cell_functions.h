#ifndef CELL_FUNCTIONS
#define CELL_FUNCTIONS

#include <stdint.h>
#include <stdbool.h>

/*
*   Vsako število je predstavljeno s 16-bitno spremenljivko
*   Informacije o spremenljivki bodo govorilo o pozicijah bitov,
*   štetih z desne proti leve.
*
*   1. bit -
*       0 - celica je nespremeljiva s strani uporabnika
*       1 - celica je spremenljiva
*
*   2.-10. - biti za označevanje notacije
*       2. bit predstavlja 1, 3. predstavlja 2...
*   ostali biti - predstavljajo vrednost znotraj celice
*       praviloma ne smejo iti čez vrednost 9
*/

// Dobi določeno notacijo iz celice
bool get_note(uint16_t n, uint8_t note_num);

// Dobi vrednost v celici
uint16_t get_value(uint16_t n);

// Dobi, če je celica spremenljiva
bool get_changable(uint16_t n);

// Zamenja vrednost določene notacije
void invert_note(uint16_t *n, uint8_t note_num);

// Nastavi vrednost določene notacije
void set_note(uint16_t *n, uint8_t note_num, bool is_set);

// Nastavi vrednost v celici
void set_value(uint16_t *n, uint16_t value);

// Nastavi, če je celica spremenljiva
void set_changable(uint16_t *n, bool changable);

#endif // CELL_FUNCTIONS
