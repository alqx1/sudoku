#include "../cell_functions.h"
#include "../pos.h"
#include "constraints.h"

bool check_hidden_singles(uint16_t sudoku[9][9], uint16_t possible[9][9]) {
    // Shranjuje, če se zgodi kakšna sprememba znotraj mreže
    bool changed = false;
    unique_in_columns(sudoku, possible, &changed);
    unique_in_rows(sudoku, possible, &changed);
    unique_in_boxes(sudoku, possible, &changed);
    return changed;
}

void unique_in_rows(
    uint16_t sudoku[9][9], uint16_t possible[9][9], bool *changed
) {
    // Uporabljeno za shranjevanje položaja, kjer se
    // je pojavila zadnja možnost
    struct pos last;

    // Iteriramo skozi vse vrste
    for (int row = 0; row < 9; row++) {
        for (int num = 1; num < 10; num++) {
            // Kolikokrat se pojavi možnost
            int num_occurance = 0;
            for (int x = 0; x < 9; x++) {
                // Če ima celica že vrednost, nadaljuj na naslednjo iteracijo
                if (get_changable(possible[row][x])) {
                    continue;
                }

                // Če je možnost za vrednost, shrani položaj in prištej k števcu
                if (get_note(possible[row][x], num)) {
                    last = (struct pos){.y = row, .x = x};
                    num_occurance++;
                }
            }

            // Če se je možnost pojavila le enkrat, vnesi novo vrednost v celico
            if (num_occurance == 1) {
                add_new_value(sudoku, possible, last, num);
                *changed = true;
                // Moramo narediti, da se ne pokvari algoritem v naslednjih
                // iteracijah
                rule_constraint(sudoku, possible, last);
            }
        }
    }
}

void unique_in_columns(
    uint16_t sudoku[9][9], uint16_t possible[9][9], bool *changed
) {
    // Podobno kot pri vrsticah, le da je zdaj iteriramo po stolpcih
    struct pos last;

    for (int column = 0; column < 9; column++) {
        for (int num = 1; num < 10; num++) {
            int num_occurance = 0;
            for (int y = 0; y < 9; y++) {
                if (get_changable(possible[y][column])) {
                    continue;
                }

                if (get_note(possible[y][column], num)) {
                    last = (struct pos){.y = y, .x = column};
                    num_occurance++;
                }
            }

            if (num_occurance == 1) {
                add_new_value(sudoku, possible, last, num);
                *changed = true;
                rule_constraint(sudoku, possible, last);
            }
        }
    }
}

void unique_in_box(
    uint16_t sudoku[9][9], uint16_t possible[9][9], int box_x, int box_y,
    bool *changed
) {
    // Podobno kot pri ostalih, le drugačna iteracija po položajih znotraj bloka
    struct pos last;

    for (int num = 1; num < 10; num++) {
        int num_occurance = 0;
        // Iteriramo po položajih v bloku
        for (int y = 0; y < 3; y++) {
            for (int x = 0; x < 3; x++) {
                if (get_changable(possible[y + box_y][x + box_x])) {
                    continue;
                }

                if (get_note(possible[y + box_y][x + box_x], num)) {
                    last = (struct pos){.y = y + box_y, .x = x + box_x};
                    num_occurance++;
                }
            }
        }

        if (num_occurance == 1) {
            add_new_value(sudoku, possible, last, num);
            *changed = true;
            rule_constraints(sudoku, possible);
        }
    }
}

void unique_in_boxes(
    uint16_t sudoku[9][9], uint16_t possible[9][9], bool *changed
) {
    // Iteriramo skozi vse začetne položaje blokov
    for (int box_y = 0; box_y < 9; box_y += 3) {
        for (int box_x = 0; box_x < 9; box_x += 3) {
            unique_in_box(sudoku, possible, box_x, box_y, changed);
        }
    }
}
