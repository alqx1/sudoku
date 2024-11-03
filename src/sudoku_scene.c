#include "sudoku_scene.h"
#include "sudoku_functions.h"
#include "cell_functions.h"
#include <stdio.h>
#include <math.h>
#include <raylib.h>
#include <stddef.h>

enum Mode mode = nums;

void run_sudoku(short window_size, struct pos *selected, uint16_t sudoku[9][9]) {
    move_cursor(selected);
    place_number(*selected, sudoku);
    sudoku_input(sudoku);
    draw_board(window_size, *selected, sudoku);
}

void draw_board(
    short window_size, struct pos selected, uint16_t const sudoku[9][9]) {
    draw_selected_box(selected, window_size);
    draw_numbers(sudoku, window_size);
    draw_sudoku_lines(window_size);
}

void draw_sudoku_lines(short window_size) {
    float padding = round(window_size / 9.f);
    for (int i = 1; i < 9; i++) {
        Vector2 vec1 = {i * padding, 0};
        Vector2 vec2 = {i * padding, window_size};
        DrawLineEx(vec1, vec2, (i % 3) == 0 ? 2 : 1, BLACK);
    }

    for (int i = 1; i < 9; i++) {
        Vector2 vec1 = {0, i * padding};
        Vector2 vec2 = {window_size, i * padding};
        DrawLineEx(vec1, vec2, (i % 3) == 0 ? 2 : 1, BLACK);
    }
}

void draw_selected_box(struct pos selected, short window_size) {
    float padding = ceilf(window_size / 9.f);
    DrawRectangle(
        selected.x * padding, selected.y * padding, padding, padding,
        (mode == nums) ? LIGHTGRAY : GRAY);
}

void draw_numbers(uint16_t const sudoku[9][9], short window_size) {
    char buf[17];
    float padding = round(window_size / 9.f);
    for (size_t y = 0; y < 9; y++) {
        for (size_t x = 0; x < 9; x++) {
            if (get_value(sudoku[y][x]) == 0) {
                struct pos cell = {x, y};

                bool notes[9];
                for (size_t i = 0; i < 9; i++) {
                    notes[i] = get_note(sudoku[y][x], i + 1);
                }

                draw_notes(window_size, cell, notes);
                continue;
            }
            sprintf(buf, "%d", get_value(sudoku[y][x]));
            short width = MeasureText(buf, padding * 0.8);
            Vector2 pos = {
                padding / 2.f - width / 2.f + padding * x,
                padding / 2.f - padding * 0.4 + padding * y};
            DrawText(
                TextFormat("%d", get_value(sudoku[y][x])), pos.x, pos.y,
                padding * 0.8, get_changable(sudoku[y][x]) ? RED : BLACK);
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
            if (!notes[y * 3 + x]) {
                continue;
            }
            sprintf(buf, "%li", y * 3 + x + 1);
            short width = MeasureText(buf, font_size);
            Vector2 pos = {
                padding * cell.x + note_padding * x + note_padding / 2.f -
                    width / 2.f,
                padding * cell.y + note_padding * y + note_padding / 2.f -
                    font_size / 2.f};
            DrawText(
                TextFormat("%d", y * 3 + x + 1), pos.x, pos.y, font_size,
                BLACK);
        }
    }
}

void move_cursor(struct pos *selected) {
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
    if (!get_changable(sudoku[selected.y][selected.x]))
        return;

    int i = GetKeyPressed();
    if (i < KEY_ZERO || i > KEY_NINE) {
        return;
    }

    if (mode == nums) {
        set_value(&sudoku[selected.y][selected.x], i - KEY_ZERO);
        return;
    }

    if (mode == notes && i == KEY_ZERO) {
        for (int j = 0; j < 9; j++) {
            set_note(&sudoku[selected.y][selected.x], j + 1, false);
        }
        return;
    }

    if (mode == notes && i != KEY_ZERO) {
        invert_note(&sudoku[selected.y][selected.x], i - KEY_ONE + 1);
        return;
    }
}

void sudoku_input(uint16_t sudoku[9][9]) {
    if (IsKeyPressed(KEY_S))
        solve(sudoku);

    if (IsKeyPressed(KEY_C))
        clear(sudoku);

    if (IsKeyPressed(KEY_A)) {
        if (mode == nums) {
            mode = notes;
        }
        else {
            mode = nums;
        }
    }
}
