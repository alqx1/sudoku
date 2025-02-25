#include "sudoku_scene.h"
#include "cell_functions.h"
#include "sudoku_functions.h"
#include <math.h>
#include <raylib.h>
#include <stddef.h>
#include <stdio.h>

enum Mode mode = nums;

// Izvede vse pomembne funkcije
void run_sudoku(
    struct config config, struct pos *selected, uint16_t sudoku[9][9]
) {
    move_cursor(selected);
    place_number(*selected, sudoku);
    sudoku_input(sudoku, config.clear_cells);
    draw_board(config.window_size, *selected, sudoku);
}

// Nariše vso mrežo
void draw_board(
    short window_size, struct pos selected, uint16_t const sudoku[9][9]
) {
    draw_selected_box(selected, window_size);
    draw_numbers(sudoku, window_size);
    draw_sudoku_lines(window_size);
}

void draw_sudoku_lines(short window_size) {
    // Izračuna razdaljo med dvema sosednjima črtama
    float line_offset = round(window_size / 9.f);

    // Nariše najprej vse navpične črte
    // Vsaka tretja črta je debelejša
    for (int i = 1; i < 9; i++) {
        // Dobimo začetek in konec črte
        Vector2 vec1 = {i * line_offset, 0};
        Vector2 vec2 = {i * line_offset, window_size};
        // Povežemo začetek in konec
        DrawLineEx(vec1, vec2, (i % 3) == 0 ? 2 : 1, BLACK);
    }

    // Nariše vse vodoravne črte, vsako tretjo debelejšo
    for (int i = 1; i < 9; i++) {
        Vector2 vec1 = {0, i * line_offset};
        Vector2 vec2 = {window_size, i * line_offset};
        DrawLineEx(vec1, vec2, (i % 3) == 0 ? 2 : 1, BLACK);
    }
}

// Označimo celico, ki je izbrana, z izstopajočo barvo
// (barvi sta različni glede na način vstavljanja)
void draw_selected_box(struct pos selected, short window_size) {
    // Dobimo razdaljo med sosednjima celicama
    float cell_offset = ceilf(window_size / 9.f);
    // Narišemo barvni kvadrat, ki pokriva celico
    DrawRectangle(
        selected.x * cell_offset, selected.y * cell_offset, cell_offset, cell_offset,
        (mode == nums) ? LIGHTGRAY : GRAY
    );
}

void draw_numbers(uint16_t const sudoku[9][9], short window_size) {
    char buf[17];
    bool notes[9];
    float padding = round(window_size / 9.f);
    float font_size = padding * 0.8;
    float half_font = padding * 0.4;
    for (size_t y = 0; y < 9; y++) {
        for (size_t x = 0; x < 9; x++) {
            // Če v celici ni vrednosti, dobi vse notacijske števke
            // in jih nariši v celico
            if (get_value(sudoku[y][x]) == 0) {
                struct pos cell = {x, y};

                for (size_t i = 0; i < 9; i++) {
                    notes[i] = get_note(sudoku[y][x], i + 1);
                }

                draw_notes(window_size, cell, notes);
                continue;
            }

            // Drugače nariši števko v celico
            
            // Dobimo širino teksta za števko
            sprintf(buf, "%d", get_value(sudoku[y][x]));
            short width = MeasureText(buf, font_size);

            // Določimo pozicijo števke (zgornji levi kot števke)
            Vector2 pos = {
                padding / 2.f - width / 2.f + padding * x,
                padding / 2.f - half_font + padding * y
            };

            // Jo narišemo v celico
            DrawText(
                TextFormat("%d", get_value(sudoku[y][x])), pos.x, pos.y,
                font_size, get_changable(sudoku[y][x]) ? RED : BLACK
            );
        }
    }
}

void draw_notes(short window_size, struct pos cell, const bool notes[9]) {
    char buf[2];
    float padding = round(window_size / 9.f);
    float note_padding = round(window_size / 27.f);
    float font_size = round(note_padding * 0.9f);
    for (size_t y = 0; y < 3; y++) {
        for (size_t x = 0; x < 3; x++) {
            // Če notacije za to števko ni, iteriraj naprej
            if (!notes[y * 3 + x]) {
                continue;
            }

            // Dobi širino teksta
            sprintf(buf, "%li", y * 3 + x + 1);
            short width = MeasureText(buf, font_size);

            // Izračuna pozicijo za pozamezno števko glede na njeno vrednost
            Vector2 pos = {
                padding * cell.x + note_padding * x + note_padding / 2.f -
                    width / 2.f,
                padding * cell.y + note_padding * y + note_padding / 2.f -
                    font_size / 2.f
            };
            // Nariše jo v celico
            DrawText(
                TextFormat("%d", y * 3 + x + 1), pos.x, pos.y, font_size, BLACK
            );
        }
    }
}

void move_cursor(struct pos *selected) {
    // Če je pritisnjena določena tipka za premik, premakni kazalec v to smer
    if ((IsKeyPressed(KEY_J) || IsKeyPressed(KEY_LEFT)) && selected->x != 0)
        selected->x--;
    if ((IsKeyPressed(KEY_L) || IsKeyPressed(KEY_RIGHT)) && selected->x != 8)
        selected->x++;
    if ((IsKeyPressed(KEY_I) || IsKeyPressed(KEY_UP)) && selected->y != 0)
        selected->y--;
    if ((IsKeyPressed(KEY_K) || IsKeyPressed(KEY_DOWN)) && selected->y != 8)
        selected->y++;
}

void place_number(const struct pos selected, uint16_t sudoku[9][9]) {
    // Če celico ne smemo spremeniti,
    // vrnemo funkcijo
    if (!get_changable(sudoku[selected.y][selected.x]))
        return;

    int i = GetKeyPressed();
    // Če pritisnjena tipka ni zaželena, pejdi ven iz funkcije
    if (i < KEY_ZERO || i > KEY_NINE) {
        return;
    }

    if (mode == nums) {
        set_value(&sudoku[selected.y][selected.x], i - KEY_ZERO);
        return;
    }

    // Če je pritisnjena številka 0 in spreminjamo notacijo
    // odstrani vse notacije
    if (mode == notes && i == KEY_ZERO) {
        for (int j = 0; j < 9; j++) {
            set_note(&sudoku[selected.y][selected.x], j + 1, false);
        }
        return;
    }

    // Dručage pa samo zapiši/zbriši notacijo
    if (mode == notes && i != KEY_ZERO) {
        invert_note(&sudoku[selected.y][selected.x], i - KEY_ONE + 1);
        return;
    }
}

void sudoku_input(uint16_t sudoku[9][9], uint16_t clear_cells) {
    // Reši celotni sudoku, če je rešitev
    if (IsKeyPressed(KEY_S))
        solve(sudoku);

    // Sprazni vse nestalne celice
    if (IsKeyPressed(KEY_C))
        clear(sudoku);

    if (IsKeyPressed(KEY_R)) {
        generate_sudoku(sudoku, clear_cells);
    }

    // Zamenjaj tip vpisovanja
    if (IsKeyPressed(KEY_A)) {
        if (mode == nums) {
            mode = notes;
        }
        else {
            mode = nums;
        }
    }
}
