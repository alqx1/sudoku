#include "../cell_functions.h"
#include "sudoku_functions.h"
#include <stddef.h>

// Preveri, če je neka števka že v vrstici/stolpcu/bloku
bool in_row(uint16_t sudoku[9][9], const int row, const int num);
bool in_col(uint16_t sudoku[9][9], const int col, const int num);
bool in_box(uint16_t sudoku[9][9], const struct pos position, const int num);

// Rekurzivna funkcija
bool solve(uint16_t sudoku[9][9]) {
    // Struktura, ki bo shranjevala pozicijo prazne celice
    struct pos empty_cell = {0, 0};

    // Če ni prazne celice, je sudoku rešen
    if (!find_empty_cell(sudoku, &empty_cell)) {
        return true;
    }

    // Poskusi vsako številko za celico
    // Če ne deluje, pojdi nazaj na prej-delujočo stanje
    // drugače pa nadaljuj z reševanjem
    for (int num = 1; num < 10; num++) {
        // Če je vrednost lahko vstavljena v celico
        if (is_safe(sudoku, empty_cell, num)) {
            // Poskusi vrednost
            set_value(&sudoku[empty_cell.y][empty_cell.x], num);

            // Če vrednost vodi k rešeni mreži, vrni true
            if (solve(sudoku)) {
                return true;
            }

            // Drugače resetiraj celico
            set_value(&sudoku[empty_cell.y][empty_cell.x], 0);
        }
    }

    // Če algoritem ne dela, pomeni da ni rešitve
    return false;
}

// Funkcija podobna kakor "solve" funkcija
void number_of_solutions(uint16_t sudoku[9][9], int *solutions) {
    struct pos empty_cell = {0, 0};

    // Če ne najde prazne celice, je to ena od rešitev,
    // vendar nadaljuje z reševanjem
    if (!find_empty_cell(sudoku, &empty_cell)) {
        *(solutions) += 1;
        return;
    }

    for (int num = 1; num < 10; num++) {
        if (is_safe(sudoku, empty_cell, num)) {
            set_value(&sudoku[empty_cell.y][empty_cell.x], num);

            number_of_solutions(sudoku, solutions);

            set_value(&sudoku[empty_cell.y][empty_cell.x], 0);
        }
    }
}

bool in_row(uint16_t sudoku[9][9], const int row, const int num) {
    for (size_t i = 0; i < 9; i++) {
        // Če je številka že v vrstici, vrni true
        if (get_value(sudoku[row][i]) == num) {
            return true;
        }
    }
    return false;
}

bool in_col(uint16_t sudoku[9][9], const int col, const int num) {
    for (size_t i = 0; i < 9; i++) {
        // Če je številka že v stolpcu, vrni true
        if (get_value(sudoku[i][col]) == num) {
            return true;
        }
    }
    return false;
}

bool in_box(uint16_t sudoku[9][9], const struct pos position, const int num) {
    // Dobimo začetne indekse bloka
    int box_x = position.x - (position.x % 3);
    int box_y = position.y - (position.y % 3);

    for (size_t i = 0; i < 3; i++) {
        for (size_t j = 0; j < 3; j++) {
            // Če je številka že v bloku, vrni true
            if (get_value(sudoku[box_y + i][box_x + j]) == num) {
                return true;
            }
        }
    }
    return false;
}

bool find_empty_cell(uint16_t sudoku[9][9], struct pos *position) {
    for (size_t i = 0; i < 9; i++) {
        for (size_t j = 0; j < 9; j++) {
            // Če je celica prazna, zapiši lokacijo v spremenljivo, vrni true
            if (get_value(sudoku[i][j]) == 0) {
                position->y = i;
                position->x = j;
                return true;
            }
        }
    }
    return false;
}

bool is_safe(uint16_t sudoku[9][9], const struct pos position, const int num) {
    // Če je celica varna za vstavljanje neke števke, morajo vse pomožne
    // funkcije vrniti false
    return (
        !in_row(sudoku, position.y, num) && !in_col(sudoku, position.x, num) &&
        !in_box(sudoku, position, num)
    );
}
