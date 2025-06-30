#ifndef _CONFIG_INCLUDE
#define _CONFIG_INCLUDE

constexpr auto WINDOW_GAME_TITLE = "GAME TITLE";
#define SCALE 3
#define TILE_SIZE (8 * SCALE)

#define GAME_TILES_X 48
#define GAME_TILES_Y 26
#define HUD_TILES_Y 4
#define GAME_WIDTH (GAME_TILES_X*TILE_SIZE)
#define GAME_HEIGTH (GAME_TILES_Y*TILE_SIZE)
#define SCREEN_WIDTH (GAME_TILES_X*TILE_SIZE)
#define SCREEN_HEIGTH ((GAME_TILES_Y + HUD_TILES_Y)*TILE_SIZE)

constexpr auto BACKGROUND_MENU = "assets/images/ui/menu.png";
constexpr auto BACKGROUND_CREDITS = "assets/images/ui/credits.png";
constexpr auto BACKGROUND = "assets/images/backgrounds/stage1-1.png";
constexpr auto TILEMAP = "assets/levels/level01.txt";

constexpr auto SPRITES_IMAGE = "assets/images/sprites.png";
constexpr auto SPRITE_SIZE = 64.f;

constexpr auto MENU_BANNER = "assets/images/ui/banner.png";

#define INIT_PLAYER_X_TILES 1
#define INIT_PLAYER_Y_TILES (GAME_TILES_Y - 2)


#define LEFT_MARGIN (1)
#define RIGHT_MARGIN (GAME_TILES_X - 1)
#define DOWN_MARGIN (GAME_TILES_Y - 1)
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

constexpr auto MUSIC_MENU = "assets/audio/music/template.mp3";
constexpr auto MUSIC_CREDITS = "assets/audio/music/template.mp3";


#endif // _CONFIG_INCLUDE
