#include "Level1.h"
#include "Config.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "Game.h"
#include "Menu.h"

namespace Scenes {
    void Level1::init() {
        Level::init();

        initShaders();
        loadLevelData();
        loadBackground();

        projection = glm::ortho(0.f, float(SCREEN_WIDTH), float(SCREEN_HEIGTH), 0.f);
        currentTime = 0.f;

        AudioManager::instance().playSound("assets/audio/music/template.mp3");
    }

    void Level1::loadLevelData() {
        map = TileMap::createTileMap("TILEMAP", texProgram);

        player = new Player(map);
        player->init(glm::ivec2(0, 0), texProgram);
        player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * TILE_SIZE, INIT_PLAYER_Y_TILES * TILE_SIZE));
    }

    void Level1::update(int deltaTime) {
        Level::update(deltaTime);

        if (Game::instance().getKeyPressed(GLFW_KEY_ESCAPE)) {
            Game::instance().loadNewScene(std::make_unique<Menu>());
        }

    }
}
