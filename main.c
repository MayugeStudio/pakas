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

#define LVL_AT(tiles, row, col) (tiles[(row*TILE_COLS)+col])

struct Tile {
    Rectangle rect;
};

struct Player {
    Rectangle rect;
};

int main(void)
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "PAKAS");


    struct Tile level[TILE_ROWS*TILE_COLS] = {0};

    for (int row=0; row<TILE_ROWS; row++) {
        for (int col=0; col<TILE_COLS; col++) {
            struct Tile *tile = &LVL_AT(level, row, col);
            tile->rect.x = col*TILE_SIZE;
            tile->rect.y = row*TILE_SIZE;
            tile->rect.width = TILE_SIZE;
            tile->rect.height = TILE_SIZE;
        }
    }

    Image display_image = GenImageColor(DISPLAY_WIDTH, DISPLAY_HEIGHT, RAYWHITE);
    Rectangle display_rect = { .x=0, .y=0, .width=DISPLAY_WIDTH, .height=DISPLAY_HEIGHT };

    // Draw background image then unload it.
    Image bg_image = LoadImage("assets/background.png");
    ImageDraw(&display_image, bg_image, display_rect, display_rect, WHITE);
    UnloadImage(bg_image);

    Texture display_texture = LoadTextureFromImage(display_image);
    Vector2 display_position = { .x=0, .y=0 };


    Image tile_image = LoadImage("assets/01-land.png");

    SetTargetFPS(60);

    struct Player player = { .rect=(Rectangle){ .x=TILE_SIZE*6+(TILE_SIZE/2), .y=TILE_SIZE*5, .width=TILE_SIZE, .height=TILE_SIZE } };

    while(!WindowShouldClose())
    {
        // Update Display Image
        {
            for (int row=6; row<TILE_ROWS; row++) {
                for (int col=0; col<TILE_COLS; col++) {
                    ImageDraw(&display_image, tile_image, display_rect, LVL_AT(level, row, col).rect, WHITE);
                }
            }

            ImageDrawRectangleRec(&display_image, player.rect, RED);
        }

        // Update Texture
        UpdateTexture(display_texture, display_image.data);

        BeginDrawing();
        {
            ClearBackground(RAYWHITE);
            DrawTextureEx(display_texture, display_position, 0.0f, (float)DISPLAY_RATIO, WHITE);
        }
        EndDrawing();
    }

    // Unload Images and Textures.
    UnloadImage(tile_image);
    UnloadImage(display_image);
    UnloadTexture(display_texture);
    CloseWindow();
}

