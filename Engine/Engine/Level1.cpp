#include "Level1.h"
#include "Config.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

void Level1::init() {
    initShaders();
    loadLevelData();
    loadBackground();

    projection = glm::ortho(0.f, float(SCREEN_WIDTH), float(SCREEN_HEIGHT), 0.f);
    currentTime = 0.f;

    AudioManager::instance().playSound("audio/music/template.mp3");
}

void Level1::loadLevelData() {
    map = TileMap::createTileMap(TILEMAP, texProgram);

    player = new Player(map);
    player->init(glm::ivec2(0, 0), texProgram);
    player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * TILE_SIZE, INIT_PLAYER_Y_TILES * TILE_SIZE));
}
