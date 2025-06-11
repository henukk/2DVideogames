#ifndef _CONFIG_INCLUDE
#define _CONFIG_INCLUDE

#define WINDOW_GAME_TITLE "GAME TITLE"
#define SCALE 2
#define SCREEN_WIDTH (384*SCALE)
#define SCREEN_HEIGHT (208*SCALE)
#define SCREEN_X 48
#define SCREEN_Y 26

#define BACKGROUND "images/backgrounds/stage1-1.png"
#define TILEMAP "levels/level01.txt"

#define SPRITES_IMAGE "images/sprites.png"
#define SPRITE_SIZE 64.f

#define INIT_PLAYER_X_TILES 1
#define INIT_PLAYER_Y_TILES (SCREEN_Y - 2)

#define TILE_SIZE (8 * SCALE)

#define LEFT_MARGIN (1)
#define RIGHT_MARGIN (SCREEN_X - 1)
#define DOWN_MARGIN (SCREEN_Y - 1)
#define TOP_MARGIN (TILE_SIZE * 1)

#define PLAYER_WIDTH (TILE_SIZE*2)
#define PLAYER_HEIGTH (TILE_SIZE*3)

#endif // _CONFIG_INCLUDE
