#include "game.h"
#include <raylib.h>
#include <stdio.h>

void draw_board(short window_size, struct pos selected, int const *sudoku) {
    draw_selected_box(selected, window_size);
    draw_numbers(sudoku, window_size);
    draw_lines(window_size);
}

void draw_lines(short window_size) {
    float padding = window_size / 9.f;
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
    float padding = window_size / 9.f;
    DrawRectangle(
        selected.x * padding, selected.y * padding, padding, padding, SKYBLUE);
}

void draw_numbers(int const *sudoku, short window_size) {
    char buf[2];
    float padding = window_size / 9.f;
    for (int y = 0; y < 9; y++) {
        for (int x = 0; x < 9; x++) {
            if (*(sudoku + 9 * y + x) == 0) continue;
            sprintf(buf, "%d", *(sudoku + 9 * y + x));
            short width = MeasureText(buf, padding * 0.8);
            Vector2 pos = {
                padding / 2.f - width / 2.f + padding * x,
                padding / 2.f - padding * 0.4 + padding * y};
            DrawText(
                TextFormat("%d", *(sudoku + 9 * y + x)), pos.x, pos.y,
                padding * 0.8, BLACK);
        }
    }
}
