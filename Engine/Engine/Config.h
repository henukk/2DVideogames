#ifndef _CONFIG_INCLUDE
#define _CONFIG_INCLUDE

constexpr auto WINDOW_GAME_TITLE = "GAME TITLE";
#define SCALE 2
#define SCREEN_WIDTH (384*SCALE)
#define SCREEN_HEIGHT (208*SCALE)
#define SCREEN_X 48
#define SCREEN_Y 26

constexpr auto BACKGROUND = "assets/images/backgrounds/stage1-1.png";
constexpr auto TILEMAP = "assets/levels/level01.txt";

constexpr auto SPRITES_IMAGE = "assets/images/sprites.png";
constexpr auto SPRITE_SIZE = 64.f;

#define INIT_PLAYER_X_TILES 1
#define INIT_PLAYER_Y_TILES (SCREEN_Y - 2)

#define TILE_SIZE (8 * SCALE)

#define LEFT_MARGIN (1)
#define RIGHT_MARGIN (SCREEN_X - 1)
#define DOWN_MARGIN (SCREEN_Y - 1)
#define TOP_MARGIN (TILE_SIZE * 1)

#define PLAYER_WIDTH (TILE_SIZE*2)
#define PLAYER_HEIGTH (TILE_SIZE*3)

constexpr auto FILE_VERTEX_SHADER_TEXTURE = "assets/shaders/texture.vert";
constexpr auto FILE_FRAGMENT_SHADER_TEXTURE = "assets/shaders/texture.frag";
constexpr auto FILE_VERTEX_SHADER_TEXT = "assets/shaders/text.vert";
constexpr auto FILE_FRAGMENT_SHADER_TEXT = "assets/shaders/text.frag";

constexpr auto FILE_ARCADE_FONT_1 = "assets/fonts/PixelifySans-VariableFont_wght.ttf";
constexpr auto FILE_ARCADE_FONT_2 = "assets/fonts/PressStart2P-Regular.ttf";
constexpr auto FILE_ARCADE_FONT_3 = "assets/fonts/Silkscreen-Bold.ttf";
constexpr auto FILE_ARCADE_FONT_4 = "assets/fonts/Silkscreen-Regular.ttf";
constexpr auto FILE_ARCADE_FONT_5 = "assets/fonts/VT323-Regular.ttf";


#endif // _CONFIG_INCLUDE
