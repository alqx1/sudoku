#include "cell_functions.h"

bool get_note(uint16_t n, uint8_t note_num) {
    // Premakne bit za notacijo na prvo mesto
    n >>= note_num;
    // Vse ostale bite nastavi na 0
    n &= 1;
    return n;
}

uint16_t get_value(uint16_t n) {
    // Premakne bite za vrednost na prva mesta
    // S tem odstrani ostale bite
    n >>= 10;
    return n;
}

bool get_changable(uint16_t n) {
    // Dobi vrednost prvega bita
    return n & 1;
}

void invert_note(uint16_t *n, uint8_t note_num) {
    // Ustvari masko z 1 na lokaciji notacije
    // Z operacijo XOR obrne vrednost bita
    *n ^= (1 << note_num);
}

void set_note(uint16_t *n, uint8_t note_num, bool is_set) {
    // Če nastavljamo notacijo na true
    if (is_set) {
        // Naredimo masko z 1 na lokaciji notacije
        // ter bit z opracijo OR spremenimo v 1
        *n |= (1 << note_num);
        return;
    }
    // Drugače naredimo masko z 0 na lokaciji notacije
    // (ostale so 1)
    // Vse bite prekopiramo, razen določenega bita, ki bo
    // z operacijo AND pretvorjen v 0
    *n &= ~(1 << note_num);
}

void set_value(uint16_t *n, uint16_t value) {
    // Nastavimo masko, ki bo prekopirala vse bite pred
    // biti z vrednostjo v celici
    uint16_t mask = ~0;
    // Prekopiramo bite
    mask >>= 6;
    *n &= mask;

    // Vrednost nastavimo na lokacijo po vseh bitih
    // o notaciji in spremenljivosti
    value <<= sizeof(uint16_t) * 8 - 2 - 4;
    // Seštejemo prvotne bite in novo vrednost
    *n += value;
}

// Podobno kot pri funkciji "set_note", vendar ni
// potrebno ustvarjati posebne maske, saj je vrednost
// 1 oz. ~1 že naša maska
void set_changable(uint16_t *n, bool changable) {
    if (changable) {
        *n |= 1;
        return;
    }
    *n &= ~1;
}
