#include "sudoku_functions.h"
#include "cell_functions.h"
#include "pos.h"
#include <stdio.h>
#include <stdlib.h>

void read_file(uint16_t sudoku[9][9], char *path) {
    FILE *fin = fopen(path, "r");
    if (fin == NULL) {
        printf("Error: Can't open file\n");
        free(fin);
        exit(2);
    }

    int count = 0;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    while ((read = getline(&line, &len, fin)) != -1 && count < 9) {
        if (read != 10) {
            printf("Error: One line contains too many/little characters\n");
            free(line);
            exit(5);
        }

        for (size_t i = 0; i < 9; i++) {
            if (line[i] > '9' || line[i] < '0') {
                printf("Error: Sudoku contains wrong numbers\n");
                free(line);
                exit(4);
            }

            sudoku[count][i] = 0;
            set_value(&sudoku[count][i], line[i] - '0');
            set_changable(&sudoku[count][i], false);
        }
        count++;
    }

    fclose(fin);
    free(line);
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
    // gets first indicies of box
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

void clear(uint16_t sudoku[9][9]) {
    // Vsako vrednost v spremljivi celici odstrani
    for (size_t i = 0; i < 9; i++) {
        for (size_t j = 0; j < 9; j++) {
            if (get_changable(sudoku[i][j])) {
                sudoku[i][j] = 0;
                set_changable(&sudoku[i][j], true);
            }
        }
    }
}

void clear_all(uint16_t sudoku[9][9]) {
    // Vsako vrednost v celici odstrani
    for (size_t i = 0; i < 9; i++) {
        for (size_t j = 0; j < 9; j++) {
            sudoku[i][j] = 0;
            set_changable(&sudoku[i][j], true);
        }
    }
}

void generate_sudoku(uint16_t sudoku[9][9], int removed_digits) {
    // Generira diagonalne bloke
    generate_diagonal_matrices(sudoku);
    // Reši sudoku do konca
    solve(sudoku);

    // Ustvarimo kopijo, če pri odstranjevanju pride do napake
    uint16_t copy[9][9];
    copy_sudoku(sudoku, copy);
    // Če pri odstranjevanju pride do napake, kopiraj originalno tabelo nazaj
    while (!remove_n_digits(sudoku, removed_digits)) {
        copy_sudoku(copy, sudoku);
    }
}

void generate_diagonal_matrices(uint16_t sudoku[9][9]) {
    for (size_t i = 0; i < 9; i++) {
        for (size_t j = 0; j < 9; j++) {
            sudoku[i][j] = 0;
        }
    }

    bool random = rand() % 2;

    int nums[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    shuffle_nums(nums);
    add_nums_to_box(sudoku, random ? 0 : 6, 0, nums);

    shuffle_nums(nums);
    add_nums_to_box(sudoku, 3, 3, nums);

    shuffle_nums(nums);
    add_nums_to_box(sudoku, random ? 6 : 0, 6, nums);
}

void shuffle_nums(int nums[9]) {
    int temp;
    for (ssize_t i = 8; i >= 0; i--) {
        short random = rand() % (i + 1);
        temp = nums[random];
        nums[random] = nums[i];
        nums[i] = temp;
    }
}

void add_nums_to_box(uint16_t sudoku[9][9], int box_x, int box_y, int nums[9]) {
    for (size_t y = 0; y < 3; y++) {
        for (size_t x = 0; x < 3; x++) {
            set_value(&sudoku[box_y + y][box_x + x], nums[y * 3 + x]);
        }
    }
}

bool remove_n_digits(uint16_t sudoku[9][9], int n) {
    int temp;
    int solutions;
    int iterations = 500; // Število največ itercij
    while (n != 0) {
        // Če se kdaj rekurzija zatakne
        if (iterations == 0)
            return false;

        // Generira naključno pozicijo
        short x = rand() % 9;
        short y = rand() % 9;

        while ((temp = get_value(sudoku[y][x])) == 0) {
            x = rand() % 9;
            y = rand() % 9;
            continue;
        }

        set_value(&sudoku[y][x], 0);

        // Preveri število rešitev, če ni samo ena rešitev, poskusi drugo celico
        solutions = 0;
        number_of_solutions(sudoku, &solutions);
        if (solutions != 1) {
            set_value(&sudoku[y][x], temp);
            continue;
        }

        // Spremeni v spremenljivo celico
        set_changable(&sudoku[y][x], true);
        n--;
    }
    return true;
}

void print_sudoku(uint16_t sudoku[9][9]) {
    for (size_t i = 0; i < 9; i++) {
        for (size_t j = 0; j < 9; j++) {
            printf("%i ", get_value(sudoku[i][j]));
        }
        printf("\n");
    }
}

void copy_sudoku(uint16_t const original_sudoku[9][9], uint16_t copy[9][9]) {
    for (size_t i = 0; i < 9; i++) {
        for (size_t j = 0; j < 9; j++) {
            copy[i][j] = original_sudoku[i][j];
        }
    }
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
