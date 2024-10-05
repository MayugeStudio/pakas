#include <stdio.h>
#include "raylib.h"

#define WINDOW_WIDTH 896
#define WINDOW_HEIGHT 640

#define DISPLAY_RATIO 4
#define DISPLAY_WIDTH (WINDOW_WIDTH/DISPLAY_RATIO)
#define DISPLAY_HEIGHT (WINDOW_HEIGHT/DISPLAY_RATIO)

#define TILE_SIZE 16
#define TILE_ROWS (DISPLAY_HEIGHT/TILE_SIZE)
#define TILE_COLS (DISPLAY_WIDTH/TILE_SIZE)

struct Tile {
    Rectangle rect;
};

int main(void)
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "PAKAS");

    Image tile_image = LoadImage("assets/01-land.png");

    struct Tile tiles[TILE_ROWS*TILE_COLS] = {0};

    for (int row=0; row<TILE_ROWS; row++) {
        for (int col=0; col<TILE_COLS; col++) {
            tiles[row*TILE_COLS+col].rect.x = col*TILE_SIZE;
            tiles[row*TILE_COLS+col].rect.y = row*TILE_SIZE;
            tiles[row*TILE_COLS+col].rect.width = TILE_SIZE;
            tiles[row*TILE_COLS+col].rect.height = TILE_SIZE;
            printf("row: %d, col: %d\n", row, col);
            printf("x: %0.f, y: %0.f\n", tiles[row*TILE_COLS+col].rect.x, tiles[row*TILE_COLS+col].rect.y);
        }
    }

    Image display = GenImageColor(DISPLAY_WIDTH, DISPLAY_HEIGHT, RAYWHITE);
    Rectangle display_rect = { .x=0, .y=0, .width=DISPLAY_WIDTH, .height=DISPLAY_HEIGHT };
    for (int row=0; row<TILE_ROWS; row++) {
        for (int col=0; col<TILE_COLS; col++) {
            struct Tile tile = tiles[row*TILE_COLS+col];
            ImageDraw(&display, tile_image, display_rect, tile.rect, WHITE);
        }
    }

    Texture display_texture = LoadTextureFromImage(display);
    Vector2 display_position = { .x=0, .y=0 };

    // Unload Images.
    UnloadImage(display);
    UnloadImage(tile_image);

    SetTargetFPS(60);

    while(!WindowShouldClose())
    {
        BeginDrawing();
        {
            ClearBackground(RAYWHITE);
            DrawTextureEx(display_texture, display_position, 0.0f, (float)DISPLAY_RATIO, WHITE);
        }
        EndDrawing();
    }
    
    // Unload Textures.
    UnloadTexture(display_texture);
    CloseWindow();
}

